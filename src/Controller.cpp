#include "Controller.h"
#include "Resources.h"

Controller::Controller()
{
	m_window.create(sf::VideoMode(winSize.x, winSize.y), "Circle the cat - by Dvir", sf::Style::Titlebar | sf::Style::Close);
	m_title = Btn(winSize.x/2.f, winSize.y/3.f, " ", false, nullptr);
	m_title.fontSize(35);
	m_btn_one = Btn(winSize.x / 4.0f, winSize.y / 2.0f, " ", true, nullptr);
	m_btn_two = Btn(winSize.x / 4.0f * 2.5, winSize.y / 2.0f, " ", true, nullptr);
}

//__________________________________
void Controller::run() {
	sf::Vector2f cursorPosF;
	while (m_window.isOpen()) {
		m_window.clear(sf::Color::White);
		sf::Event event;
		cursorPosF = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		while (m_window.pollEvent(event)) {
			switch (screen)
			{
			default:
				throw std::invalid_argument("Unknown enum entery used!");
				break;
			case Screen::Game:			whilePlaying(event, cursorPosF);	break;
			case Screen::WinScreen:		winningScreen(event, cursorPosF);	break;
			case Screen::LoseScreen:	failedScreen(event, cursorPosF);	break;
			}

		}
		auto delta = m_gameClock.restart();
		if (screen == Screen::Game) {
			m_board.draw(m_window);
			m_board.update(m_gameClock.restart());
		}
		else {
			m_title.draw(m_window);
			m_btn_one.draw(m_window);
			m_btn_two.draw(m_window);
		}

		m_window.display();

	}
}


void Controller::whilePlaying(sf::Event event, sf::Vector2f cursorPosF) {

	switch (event.type) {
	case sf::Event::Closed:
		m_window.close();
		break;
	case sf::Event::MouseMoved:
		m_board.hover(cursorPosF);
		break;
	case sf::Event::MouseButtonReleased:
		try {
			m_board.handleClick(cursorPosF);
			break;
		}
		catch (std::exception& e) {
			if (strcmp(e.what(), "you win") == 0) 
				screen = Screen::WinScreen;
			else if (strcmp(e.what(), "you lose") == 0) {
				m_window.clear(sf::Color::White);
				m_board.draw(m_window);
				m_window.display();
				screen = Screen::LoseScreen;
				sf::sleep(sf::seconds(0.5));
			}
		}
	}

}

void Controller::failedScreen(sf::Event event, sf::Vector2f cursorPosF) {
	m_title.updateString("You Failed!",sf::Vector2f(winSize.x /2, m_title.getPosition().y));
	m_btn_one.updateString("Try Agian");
	m_btn_two.updateString("Shuffle Board");
	m_btn_one.updatFunc([this]() { m_board.playSameLevel(false); screen = Screen::Game; });
	m_btn_two.updatFunc([this]() { m_board.buildGrid(); screen = Screen::Game; });

	switch (event.type) {
	case sf::Event::Closed:
		m_window.close();
		break;
	case sf::Event::MouseMoved:
		m_btn_one.hover(cursorPosF);
		m_btn_two.hover(cursorPosF);
		break;
	case sf::Event::MouseButtonReleased:
		m_btn_one.Press(cursorPosF);
		m_btn_two.Press(cursorPosF);
	}
}

void Controller::winningScreen(sf::Event event, sf::Vector2f cursorPosF) {
	m_title.updateString("You pass the Level!", sf::Vector2f(winSize.x / 2, m_title.getPosition().y));
	m_btn_one.updateString("Play Same Board");
	m_btn_two.updateString("Next Level");
	m_btn_one.updatFunc([this]() { m_board.playSameLevel(true); screen = Screen::Game; });
	m_btn_two.updatFunc([this]() { m_board.buildGrid(); screen = Screen::Game; });

	switch (event.type) {
	case sf::Event::Closed:
		m_window.close();
		break;
	case sf::Event::MouseMoved:
		m_btn_one.hover(cursorPosF);
		m_btn_two.hover(cursorPosF);
		break;
	case sf::Event::MouseButtonReleased:
		m_btn_one.Press(cursorPosF);
		m_btn_two.Press(cursorPosF);
	}
}
