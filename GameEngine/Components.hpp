#pragma once

#include "Vector2.hpp"

class CCollision
{
public:
	float radius = 0.f;

	CCollision() {}
	CCollision(float r) : radius(r) {}
};

class CFont
{
public:
	sf::Font font;

	CFont() {}
};

class CLifespan
{
public:
	int remaining = 0;
	int total = 0;
	CLifespan(int tot) : remaining(tot), total(tot) {}
};

class CScore
{
public:
	int score = 0;

	CScore(int s) : score(s) {}
};

class CShape
{
public:
	sf::CircleShape circleShape;
	sf::RectangleShape rectShape;

	CShape() {}
	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)
		: circleShape(radius, points)
	{
		circleShape.setFillColor(fill);
		circleShape.setOutlineColor(outline);
		circleShape.setOutlineThickness(thickness);
		circleShape.setOrigin(radius, radius);
	}
	CShape(float width, float height, const sf::Color& fill)
		: rectShape(sf::Vector2f(width, height))
	{
		rectShape.setFillColor(fill);
		rectShape.setOrigin(sf::Vector2f(width * 0.5f, height * 0.5f));
	}
};

class CText
{
public:
	sf::Text text;

	CText() {}
};

class CTransform
{
public:
	Vector2 position;
	Vector2 velocity;
	Vector2 scale;
	Vector2 offset;
	float angle = 0.f;

	CTransform() {}
	CTransform(const Vector2& pos, const Vector2& vel, float a)
		: position(pos), velocity(vel), angle(a) {}
};