#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <functional>

class Board;
//that class will show button or title on the board
class Btn {
private:
	sf::Text		m_string;
	sf::Vector2f	m_position;
	sf::Sound		m_sound;
	bool			m_isButton = false;
	std::function<void(void)>		    m_func;
public:
	Btn() = default;
	Btn(float, float, sf::String, bool, std::function<void(void)> func);
	void hover(const sf::Vector2f cursur);
	void Press(const sf::Vector2f cursur);
	void updateString(sf::String, sf::Vector2f pos = { 0.f, 0.f });
	void fontSize(unsigned int);
	auto getPosition() const { return m_position; };
	void updatFunc(std::function<void(void)> func) { m_func = func; };
	void draw(sf::RenderWindow &window) const;
};