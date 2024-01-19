#include "Animation.hpp"
#include <cmath>
#include <iostream>

Animation::Animation(const std::string& name, const sf::Texture& t)
	: Animation(name, t, 1, 0)
{}

Animation::Animation(const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed)
	: m_name(name)
	, m_sprite(t)
	, m_frameCount(frameCount)
	, m_currentFrame(0)
	, m_speed(speed)
{
	m_size = Vector2((float)t.getSize().x / frameCount, (float)t.getSize().y);
	m_sprite.setOrigin(m_size.x / 2.f, m_size.y / 2.f);
	m_sprite.setTextureRect(sf::IntRect(std::floor(m_currentFrame) * m_size.x, 0, m_size.x, m_size.y));
}

void Animation::update()
{
	m_currentFrame++;

	//Calculate correct frame of anim based on currentFrame and speed, set textureRect
	if (m_currentFrame != 0 && m_speed != 0 && m_currentFrame % m_speed == 0)
	{
		int frame = (int)(m_currentFrame / m_speed) % m_frameCount;

		m_sprite.setTextureRect(sf::IntRect((int)(frame * m_size.x), 0, m_size.x, m_size.y));
	}
}

bool Animation::hasEnded() const
{
	return ((float)m_currentFrame / m_speed >= m_frameCount);
}