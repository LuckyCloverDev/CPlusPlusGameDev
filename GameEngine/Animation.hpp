#pragma once

#include <SFML/Graphics.hpp>
#include "Vector2.hpp"

class Animation
{
	sf::Sprite  m_sprite;
	size_t      m_frameCount   = 1;
	size_t      m_currentFrame = 0;
	size_t      m_speed        = 0;
	Vector2     m_size         = { 1, 1 };
	std::string m_name         = "none";
public:
	Animation() {}
	Animation(const std::string& name, const sf::Texture& t);
	Animation(const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed);

	void               update();
	bool               hasEnded() const;
	const std::string& getName() const { return m_name; }
	const Vector2&     getSize() const { return m_size; }
	sf::Sprite&        getSprite()     { return m_sprite; }
};