#pragma once
#include "Resources.h"
#include "board.h"
#include "Btn.h";

static const sf::Vector2u winSize = sf::Vector2u(560, 560);


class Controller {
public:
	Controller();
	void run();
private:
	Board				m_board;
	sf::Clock			m_gameClock;
	Btn					m_title;
	Btn					m_btn_one;
	Btn					m_btn_two;
	sf::RenderWindow	m_window;
	int					m_level = 1;

	void whilePlaying(sf::Event, sf::Vector2f );
	void winningScreen(sf::Event, sf::Vector2f );
	void failedScreen(sf::Event, sf::Vector2f );

	enum class Screen
	{
		Game,
		WinScreen,
		LoseScreen,
	};

	Screen screen = Screen::Game;
};

