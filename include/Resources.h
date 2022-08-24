#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "AnimationData.h"



class Resources {

public:
	static Resources& instance();


	const sf::Font& getFont();
	const sf::SoundBuffer& getSound();
	const sf::Texture& getSprite();
	const AnimationData& animationData( ) { return m_data; }

private:
	Resources();
	Resources(const Resources&) = delete;
	void operator=(const Resources&) = delete;

	sf::SoundBuffer m_sound;
	sf::Sprite		m_sprite;
	sf::Texture		m_texture;
	sf::Font		m_font;
	AnimationData	m_data;
};