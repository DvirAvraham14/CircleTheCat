#include "Resources.h"
#include <iostream>


namespace
{
	AnimationData cat()
	{
		const auto size = sf::Vector2i(32, 27);

		auto cat = AnimationData{};
		cat.m_data[Direction::Stay].emplace_back(sf::Vector2i(0, 0), size);
		cat.m_data[Direction::Stay].emplace_back(sf::Vector2i(32, 0), size);
		cat.m_data[Direction::Stay].emplace_back(sf::Vector2i(64, 0), size);

		cat.m_data[Direction::Left].emplace_back(sf::Vector2i(0,  27), size);
		cat.m_data[Direction::Left].emplace_back(sf::Vector2i(32, 27), size);
		cat.m_data[Direction::Left].emplace_back(sf::Vector2i(64, 27), size);

		cat.m_data[Direction::UpLeft].emplace_back(sf::Vector2i(0,  54), size);
		cat.m_data[Direction::UpLeft].emplace_back(sf::Vector2i(32, 54), size);
		cat.m_data[Direction::UpLeft].emplace_back(sf::Vector2i(64, 54), size);

		cat.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(0, 27*3), size);
		cat.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(32, 27*3), size);
		cat.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(64, 27*3), size);

		cat.m_data[Direction::Right].emplace_back(sf::Vector2i(0,  27*4), size);
		cat.m_data[Direction::Right].emplace_back(sf::Vector2i(32, 27*4), size);
		cat.m_data[Direction::Right].emplace_back(sf::Vector2i(64, 27*4), size);

		cat.m_data[Direction::DownRight].emplace_back(sf::Vector2i(0,  27*5), size);
		cat.m_data[Direction::DownRight].emplace_back(sf::Vector2i(32, 27*5), size);
		cat.m_data[Direction::DownRight].emplace_back(sf::Vector2i(64, 27*5), size);

		cat.m_data[Direction::UpRight].emplace_back(sf::Vector2i(0,  27*6), size);
		cat.m_data[Direction::UpRight].emplace_back(sf::Vector2i(32, 27*6), size);
		cat.m_data[Direction::UpRight].emplace_back(sf::Vector2i(64, 27*6), size);

		return cat;
	}
}

Resources::Resources()
{
	if (!m_font.loadFromFile("gameFont.otf"))
		std::cerr << "Font error\n";
	if (!m_sound.loadFromFile("coll.wav"))
		std::cerr << "sound loading failed\n";
	if (!m_texture.loadFromFile("cats.png"))
		std::cerr << "cat failed loaing\n";
	m_data = cat();
}

//__________________________________
Resources& Resources::instance()
{
	static Resources instance;
	return instance;
}

//__________________________________
const sf::Font& Resources::getFont() {
	return m_font;
}

//__________________________________
const sf::SoundBuffer& Resources::getSound() {
	return m_sound;
}

//__________________________________
const sf::Texture& Resources::getSprite() {
	return m_texture;
}

