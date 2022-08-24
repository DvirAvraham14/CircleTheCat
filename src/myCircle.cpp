#include "myCircle.h"

//__________________________________
void myCircle::hover(const sf::Vector2f cursur) {
	if (!m_isPreesed && !m_isCat)
		if (this->getGlobalBounds().contains(cursur))
			this->setFillColor(sf::Color(0xfcfc49ff));
		else
			this->setFillColor(sf::Color(0xacfc49ff));
}

//__________________________________
bool myCircle::Press(const sf::Vector2f cursur) {
	if (!m_isPreesed && !m_isCat)
		if (this->getGlobalBounds().contains(cursur)) {
			this->setFillColor(sf::Color(0x649457ff));
			m_isPreesed = true;
			m_sound.play();
			return true;
		}
	return false;
}

//__________________________________
void myCircle::Press(bool set) {
	this->m_isPreesed = set;
	if(set)
		this->setFillColor(sf::Color(0x649457ff));
	else
		this->setFillColor(sf::Color(0xacfc49ff));

}

//__________________________________
void myCircle::setCat() {
	this->m_isCat = true;
}

//__________________________________
void myCircle::disableCat() {
	this->m_isCat = false;
}

//__________________________________
void myCircle::posInBoard(int x, int y) {
	m_position = std::make_pair(x, y);
}

//__________________________________
std::pair<int, int> myCircle::getPosInBoard() const {
	return m_position;
}
