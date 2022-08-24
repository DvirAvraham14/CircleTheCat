#include "theCat.h"
#include <iostream>
#include "Resources.h"


//__________________________________
theCat::theCat()
	:m_animation(Resources::instance().animationData(), Direction::Stay, m_cat)
{
	this->m_cat.scale(1.3, 1.3);
	this->m_cat.setOrigin(m_cat.getLocalBounds().width / 2.f, m_cat.getLocalBounds().height / 2.f);
}

//__________________________________
theCat::theCat(sf::Vector2f position)
	:theCat()
{
	//this->m_cat.setTexture(Resources::instance().getSprite());
	this->m_cat.setPosition(position);

}

//__________________________________
void theCat::setPosition(sf::Vector2i posIndex, sf::Vector2f target, sf::Vector2f position) {
	if (posIndex.x == 0 || posIndex.x == 10 || posIndex.y == 0 || posIndex.y == 10)
		throw std::exception("you lose");
	m_catPos = posIndex;
	this->m_catPosTarget = target;
	this->m_cat.setPosition(position);

}

//__________________________________
bool theCat::vaildPosition(const std::pair<int, int> pos) {
	return ((this->m_catPos.x != pos.first || this->m_catPos.y != pos.second) &&
		!(pos.first == 0 || pos.first == 10 || pos.second == 0 || pos.second == 10));
}

//__________________________________
bool theCat::update(sf::Time delta, Direction dir)
{
	std::pair<Direction, sf::Vector2f> Dire(getDir(m_cat.getPosition(), m_catPosTarget, true));
	if (Dire.second.x == 0 && Dire.second.y == 0) 
		m_animation.direction(Direction::Stay);
	else
		m_animation.direction(dir);

	m_cat.move( Dire.second * delta.asSeconds() * 40.0f);
	m_animation.update(delta);
	return ((Dire.second.x == 0) && (Dire.second.y == 0)) ? true : false;
}