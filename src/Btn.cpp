#include "Btn.h"
#include "Resources.h"

//that class will show button or title on the board

Btn::Btn(float x, float y, sf::String string, bool isBtn, std::function<void(void)> func)
	:m_position({ x, y }), m_isButton(isBtn), m_func(func)
{
	m_string.setString(string);
	m_string.setFont(Resources::instance().getFont());
	m_string.setCharacterSize(20);
	m_string.setStyle(sf::Text::Bold);
	m_string.setFillColor(sf::Color::Black);
	m_string.setOrigin(m_string.getGlobalBounds().width / 2, m_string.getGlobalBounds().height / 2);
	m_string.setPosition({ x, y });
	m_sound.setBuffer(Resources::instance().getSound());
}


//__________________________________
void Btn::hover(const sf::Vector2f cursur) {
	if (m_isButton) {
		
		if (this->m_string.getGlobalBounds().contains(cursur)) {
			this->m_string.setFillColor(sf::Color::Green);
			if (m_sound.getStatus() == sf::Sound::Stopped)
				m_sound.play();
		}
		else
			this->m_string.setFillColor(sf::Color::Black);
	}
}

//__________________________________
void Btn::Press(const sf::Vector2f cursur) {
	if (m_isButton && this->m_string.getGlobalBounds().contains(cursur)) {
		this->m_string.setFillColor(sf::Color(0x649457ff));
		m_func();
	}
}

//__________________________________
void Btn::updateString(sf::String str, sf::Vector2f pos) {
	m_string.setString(str);
	if (pos.x != 0.f) {
		m_string.setOrigin(m_string.getGlobalBounds().width / 2.f, m_string.getGlobalBounds().height / 2.f);
		m_string.setPosition(pos);
	}
}

//__________________________________
void Btn::fontSize(unsigned int size) {
	m_string.setCharacterSize(size);
}


//__________________________________
void Btn::draw(sf::RenderWindow& window) const {
	window.draw(m_string);
}
