#pragma once

#include "Components.hpp"
#include "Entity.hpp"

class Physics
{
public:
	Vector2 GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
	Vector2 GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
	bool isColliding(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
};