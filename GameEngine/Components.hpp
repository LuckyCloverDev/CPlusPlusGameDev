#pragma once

#include "Vector2.hpp"
#include "Animation.hpp"


class Component
{
public:
	bool has = false;
};


class CAnimation : public Component
{
public:
	Animation animation;
	bool repeat = false;

	CAnimation() {}
	CAnimation(const Animation& anim, bool r) : animation(anim), repeat(r) {}
};

class CBoundingBox : public Component
{
public:
	Vector2 size;
	Vector2 halfSize;

	CBoundingBox() : size(0, 0), halfSize(0, 0) {}
	CBoundingBox(float x, float y) : size(x, y), halfSize(x * 0.5f, y * 0.5f) {}
	CBoundingBox(Vector2 s)    : size(s), halfSize(s * 0.5f) {}
};

class CCollision : public Component
{
public:
	float radius = 0.f;

	CCollision() {}
	CCollision(float r) : radius(r) {}
};

class CFont : public Component
{
public:
	sf::Font font;

	CFont() {}
};

class CGravity : public Component
{
public:
	float gravity = 0.f;

	CGravity() {}
	CGravity(float g) : gravity(g) {}
};

class CInput : public Component
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool shoot = false;
	bool canShoot = true;
	bool canJump = true;

	CInput() {}
};

class CLifespan : public Component
{
public:
	int remaining = 0;
	int total = 0;

	CLifespan() {}
	CLifespan(int tot) : remaining(tot), total(tot) {}
};

class CRaycast : public Component
{
public:
	Vector2 castTo = Vector2(0, 0);

	CRaycast() {}
	CRaycast(float x, float y) : castTo(x, y) {}
	CRaycast(Vector2 castCoords) : castTo(castCoords) {}
};

class CScore : public Component
{
public:
	int score = 0;

	CScore() {}
	CScore(int s) : score(s) {}
};

class CState : public Component
{
public:
	std::string state = "jumping";

	CState() {}
	CState(const std::string& s) : state(s) {}
};

class CShape : public Component
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

class CText : public Component
{
public:
	sf::Text text;

	CText() {}
};

class CTransform : public Component
{
public:
	Vector2 position     = { 0, 0 };
	Vector2 prevPosition = { 0, 0 };
	Vector2 velocity     = { 0, 0 };
	Vector2 scale        = { 1, 1 };
	Vector2 offset       = { 0, 0 };
	float angle = 0.f;

	CTransform() {}
	CTransform(const Vector2& pos)
		: position(pos), prevPosition(pos), velocity(Vector2(0, 0)), angle(0) {}
	CTransform(const Vector2& pos, const Vector2& vel, float a)
		: position(pos), prevPosition(pos), velocity(vel), angle(a) {}
};