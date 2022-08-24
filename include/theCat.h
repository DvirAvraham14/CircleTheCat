#pragma once
#include <SFML\Graphics.hpp>
#include "Direction.h"
#include "Animation.h"
class myCricle;

const
class theCat {

public:
    theCat();
    theCat(sf::Vector2f);

    void draw(sf::RenderWindow& window) const { window.draw(m_cat); };
    sf::Vector2i getIndexPosition() const { return m_catPos; };
    sf::Vector2f getPixPosition() const { return m_cat.getPosition(); };
    void setPosition(sf::Vector2i posIndex, sf::Vector2f, sf::Vector2f );
    bool update(sf::Time delta, Direction dir);
    bool vaildPosition(const std::pair<int, int>);
   
private:
	sf::Vector2i m_catPos       = { 5, 5}; // for bfs prev neg
    sf::Vector2f m_catPosTarget;
    sf::Sprite m_cat;
    Direction m_dir = Direction::Stay;
    Animation m_animation;
    sf::Clock m_aiTime;

};
