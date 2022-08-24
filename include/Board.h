#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include <stack>
#include <format>


#include "myCircle.h"
#include "theCat.h"
#include "Btn.h"


using std::vector;

const float			RADIUS = 20.0f;
const short int		BOARD_SIZE = 11;
const unsigned int	INF = BOARD_SIZE * BOARD_SIZE;

class Board {


public:
	Board();
	void hover(const sf::Vector2f);
	void handleClick(const sf::Vector2f cursurPos);
	void buildGrid();
	void undo();
	void playSameLevel(bool);
	void update(sf::Time);
	void draw(sf::RenderWindow& window) const;

	struct undoStep
	{
		std::pair<int, int> m_catPrev;
		std::pair<int, int> m_preesedPrev;
	};

private:
	using boardVar = vector<vector<myCircle>>;
	using randCell = vector< std::pair<int, int>>;
	boardVar						m_board;
	theCat							m_cat;
    vector<vector<sf::Vector3i>>	m_bfsPath;
	vector<Btn>						m_button;
	std::stack<undoStep>			m_moves;
	bool							m_turn = true; // true is user 
	unsigned int					m_level = 1;
	Direction						m_dir = Direction::Stay;

    void					bfsPath();
	void					setSetting(int x, int y);
	void					saveLastMove(const myCircle& circle);
	void					blockedCells(randCell &);
	void					moveCat();
	bool					inBoard(sf::Vector2i position);
	bool					inBoard(std::pair<int,int> position);
	int						blockedNum();
    vector<sf::Vector2i>	getNeighbors(const sf::Vector2i position);
    vector<sf::Vector2i>	getShifts(const int row);
	std::pair<int, int>		getMinPoint() const;
	std::pair<int, int>		randomMove();
};

