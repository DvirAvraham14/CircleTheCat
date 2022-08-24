#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Resources.h"

class myCircle : public sf::CircleShape {

public:
	using sf::CircleShape::CircleShape;
	void hover(const sf::Vector2f);
	bool Press(const sf::Vector2f);
	void Press(bool set);
	void loadSound() { m_sound.setBuffer(Resources::instance().getSound()); };
	bool reachable() const { return m_isPreesed; };
	void setCat();
	void disableCat();
	void posInBoard(int x, int y);
	std::pair<int, int> getPosInBoard() const;
	void unreachable() { m_isPreesed = true; this->setFillColor(sf::Color(0x649457ff));
	};
private:
	bool m_isPreesed	= false;
	bool m_isCat		= false;
	std::pair<int, int> m_position;
	sf::Sound m_sound;
};


