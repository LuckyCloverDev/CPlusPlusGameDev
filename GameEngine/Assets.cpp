#include "Assets.hpp"
#include "iostream"

void Assets::addTexture(const std::string& name, const std::string& path)
{
	sf::Texture texture = sf::Texture();
	texture.loadFromFile(path);
	m_textures.insert({ name, texture });
}

void Assets::addAnimation(const std::string& name, const Animation& animation)
{
	m_animations.insert({ name, animation });
}

void Assets::addSound(const std::string& name, const std::string& path)
{
	sf::SoundBuffer buffer = sf::SoundBuffer();
	buffer.loadFromFile(path);
	sf::Sound sound = sf::Sound(buffer);
	m_sounds.insert({ name, sound });
}

void Assets::addFont(const std::string& name, const std::string& path)
{
	sf::Font font = sf::Font();
	if (font.loadFromFile(path))
	{
		std::cout << "\tLOADED FONT " << path << " CORRECTLY" << std::endl;
	}
	m_fonts.insert({ name, font });
}

sf::Texture& Assets::getTexture(const std::string& name)
{
	sf::Texture& texture = m_textures[name];
	return texture;
}

Animation& Assets::getAnimation(const std::string& name)
{
	Animation& anim = m_animations[name];
	return anim;
}

sf::Sound& Assets::getSound(const std::string& name)
{
	sf::Sound& sound = m_sounds[name];
	return sound;
}

sf::Font& Assets::getFont(const std::string& name)
{
	sf::Font& font = m_fonts[name];
	return font;
}