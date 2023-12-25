#pragma once

#include "Vector2.hpp"

class CTransform
{
public:
	Vector2 position;
	Vector2 velocity;
	Vector2 scale;
	float angle = 0.f;

	CTransform() {}
};