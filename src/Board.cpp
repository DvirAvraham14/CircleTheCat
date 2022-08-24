#include "Board.h"
#include <queue>
#include <random>
#include <algorithm>
#include <iterator>
#include "macro.h"

//__________________________________
Board::Board()
{
	m_button.push_back(Btn(500, 530, "undo", true, [this]() { undo(); }));
	m_button.push_back(Btn(260, 530, std::format("You Clicked: {} times", 0), false, nullptr));
	m_button.push_back(Btn(30, 530, "Reset", true, [this]() { buildGrid();  }));
	m_board.assign(BOARD_SIZE, (vector<myCircle>(BOARD_SIZE, myCircle(RADIUS))));
	buildGrid();
}

//__________________________________
void Board::buildGrid() {
	randCell shuffle;
	while (m_moves.size() > 0)
		m_moves.pop();
	for (auto r = 0; r < BOARD_SIZE; r++) {
		for (auto c = 0; c < BOARD_SIZE; c++) {
			setSetting(r, c);
			shuffle.push_back(std::make_pair(r, c));
		}
	}
	
	m_button[0].updatFunc([this]() { undo(); });
	m_button[1].updateString(std::format("You Clicked: {} times", 0));
	m_button[2].updatFunc([this]() { buildGrid(); });
	m_cat.setPosition({ 5,5 }, m_board[5][5].getPosition(), m_board[5][5].getPosition());
	m_board[5][5].setCat();
	blockedCells(shuffle); // need tp update by level
	

}

//__________________________________
void Board::setSetting(int x, int y) {
	m_board[x][y].setPointCount(6);
	m_board[x][y].disableCat();
	m_board[x][y].loadSound();
	m_board[x][y].setOrigin(m_board[x][y].getGlobalBounds().width / 2.0f, m_board[x][y].getGlobalBounds().height / 2.0f);
	if (y % 2 != 0)
		m_board[x][y].setPosition((x + 1) * (RADIUS * 2.2f) + RADIUS, (y + 1) * RADIUS * 2.2f);
	else
		m_board[x][y].setPosition((x + 1) * (RADIUS * 2.2f), (y + 1) * RADIUS * 2.2f);
	m_board[x][y].setFillColor(sf::Color(0xacfc49ff));
	m_board[x][y].posInBoard(x, y);
	m_board[x][y].Press(false);
}

//__________________________________
void Board::hover(const sf::Vector2f cursurPos) {
	for (auto& line : m_board)
		for (auto& circle : line)
			circle.hover(cursurPos);
	for (auto& btn : m_button)
		btn.hover(cursurPos);
}

//__________________________________
void Board::handleClick(const sf::Vector2f cursurPos) {
	for (auto& line : m_board)
		for (auto& circle : line)
			if (m_turn && circle.Press(cursurPos)) {
	
				bfsPath();
				saveLastMove(circle);
				moveCat();
				m_button[1].updateString(std::format("You Clicked: {} times", m_moves.size()));
			}
	for (auto& btn : m_button)
		btn.Press(cursurPos);

}

//__________________________________
void Board::saveLastMove(const myCircle & circle) {
	undoStep prev;
	prev.m_catPrev.first = m_cat.getIndexPosition().x;
	prev.m_catPrev.second = m_cat.getIndexPosition().y;
	prev.m_preesedPrev = circle.getPosInBoard();
	m_moves.push(prev);
}

//__________________________________
vector<sf::Vector2i> Board::getNeighbors(const sf::Vector2i position)
{
	//set vector to hold the result x as row y as col
	vector<sf::Vector2i> shifts = getShifts(position.y);
	std::vector<sf::Vector2i> neighbors;
	sf::Vector2i next;
	for (auto i = 0; i < shifts.size(); i++)
	{
		next = position + shifts[i];
		if (inBoard(next) && !m_board[next.x][next.y].reachable())
			neighbors.push_back(next);
	}
	return neighbors;
}

//__________________________________
vector<sf::Vector2i> Board::getShifts(const int row) {
	vector<sf::Vector2i> shifts = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
	if (row % 2 == 0) {
		shifts.push_back({ -1, 1 });
		shifts.push_back({ -1, -1 });
	}
	else {
		shifts.push_back({ 1, 1 });
		shifts.push_back({ 1, -1 });
	}
	return shifts;
}

//__________________________________
bool Board::inBoard(sf::Vector2i position) {
	return !(position.x < 0 || position.x >= BOARD_SIZE || position.y < 0 || position.y >= BOARD_SIZE);
}

//__________________________________
bool Board::inBoard(std::pair<int, int> position) {
	return inBoard(sf::Vector2i(position.first, position.second));
}

//__________________________________
void Board::bfsPath() {
	sf::Vector2i start(m_cat.getIndexPosition());
	vector<vector<sf::Vector3i>> bfsTree;
	m_bfsPath.assign(BOARD_SIZE, vector<sf::Vector3i>(BOARD_SIZE, sf::Vector3i(-1, -1, INF)));
	m_bfsPath[start.y][start.x].z = 0;
	//set a queue to hold cordinate
	std::queue<sf::Vector2i> que;
	//put cordinate in the queue
	que.push(start);

	while (!que.empty())
	{
		//take a cordinate from the queue
		sf::Vector2i current = que.front();
		que.pop();
		//set a vector of all the legal neighboors
		std::vector<sf::Vector2i> neighbors = getNeighbors(current);
		//check all the neighbors and set them ways
		for (auto& next : neighbors)
		{
			//if its a good neighbor, set his way
			if ((next.y != start.y || next.x != start.x)
				&& (m_bfsPath[next.y][next.x].z == INF))
			{
				que.push(next);
				m_bfsPath[next.y][next.x].z = m_bfsPath[current.y][current.x].z + 1;
				m_bfsPath[next.y][next.x].x = current.x;
				m_bfsPath[next.y][next.x].y = current.y;
			}
		}
	}
}

//__________________________________
std::pair<int, int> Board::getMinPoint() const {
	int min = INF;
	std::pair<int, int> point;
	for (auto x = 0; x < BOARD_SIZE; x++)
		for (auto y = 0; y < BOARD_SIZE; y++)
			if (x == 0 || x == BOARD_SIZE - 1 || y == 0 || y == BOARD_SIZE - 1)
				if (m_bfsPath[x][y].z < min) {
					min = m_bfsPath[x][y].z;
					point = std::make_pair(x, y);
				}
	if (min != INF)
		return point;
	else
		return std::make_pair(-1, -1);
}

//__________________________________
void Board::moveCat() {
	std::pair<int, int> point = getMinPoint();
	if (point.first != -1 )
		while (m_bfsPath[m_bfsPath[point.first][point.second].y][m_bfsPath[point.first][point.second].x].z != 0)
			point = std::make_pair(m_bfsPath[point.first][point.second].y, m_bfsPath[point.first][point.second].x);
	else 
		point = randomMove();

	if (point.first != -1) {
		m_dir = toDir(m_cat.getIndexPosition().y % 2 == 0,
			sf::Vector2f(point.first - m_cat.getIndexPosition().y, point.second - m_cat.getIndexPosition().x));
		m_board[m_cat.getIndexPosition().x][m_cat.getIndexPosition().y].disableCat();
		m_board[point.second][point.first].setCat();
		m_cat.setPosition({ point.second, point.first }, m_board[point.second][point.first].getPosition(), m_cat.getPixPosition());
	}
	else {
		m_level++;
		throw std::exception("you win");
	}
}

//__________________________________
void Board::blockedCells(randCell& cells) {
	std::shuffle(cells.begin(), cells.end(), std::default_random_engine(time(0)));
	auto toBlock = blockedNum();
	for (auto& c : cells) {
		if (m_cat.vaildPosition(c)) {
			m_board[c.first][c.second].Press(true);
			--toBlock;
		}
		if (toBlock == 0)
			return;
	}
}

//__________________________________

int Board::blockedNum() {
	if (m_level <= L_EASY.first)
		return L_EASY.second;
	else if (m_level <= L_MED.first)
		return L_MED.second;
	else
		return L_HARD.second;
}



//__________________________________
std::pair<int, int> Board::randomMove() {
	std::vector<sf::Vector2i> neighbors = getNeighbors(m_cat.getIndexPosition());
	std::shuffle(neighbors.begin(), neighbors.end(), std::default_random_engine(time(0)));
	//check all the neighbors and set them ways
	for (auto& next : neighbors)
		if (!m_board[next.x][next.y].reachable())
			return std::make_pair(next.y, next.x);
	return std::make_pair(-1, -1);
}

//__________________________________
void Board::undo() {
	if (m_moves.size() > 0) {
		undoStep point = m_moves.top();
		m_moves.pop();
		m_board[m_cat.getIndexPosition().x][m_cat.getIndexPosition().y].disableCat();
		m_board[point.m_catPrev.first][point.m_catPrev.second].setCat();

		m_cat.setPosition({ point.m_catPrev.first, point.m_catPrev.second },
			m_board[point.m_catPrev.first][point.m_catPrev.second].getPosition(),
			m_board[point.m_catPrev.first][point.m_catPrev.second].getPosition());

		m_board[point.m_preesedPrev.first][point.m_preesedPrev.second].Press(false);
		m_button[1].updateString(std::format("You Clicked: {} times", m_moves.size()));
	}
}

void Board::playSameLevel(bool decLevel) {
	while(!m_moves.empty())
		undo();
	if (decLevel)
		m_level--;
}

void Board::update(sf::Time delta) {
	m_turn = m_cat.update(delta, m_dir);
}

//__________________________________
void Board::draw(sf::RenderWindow& window) const {
	for (auto line : m_board)
		for (auto circle : line)
			window.draw(circle);
	for (auto& btn : m_button)
		btn.draw(window);
	m_cat.draw(window);
}