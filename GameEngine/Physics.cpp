#include "Physics.hpp"

Vector2 Physics::GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
	if (!a->hasComponent<CBoundingBox>() || !b->hasComponent<CBoundingBox>()) return Vector2(0, 0);

	auto& ta = a->getComponent<CTransform>();
	auto& bba = a->getComponent<CBoundingBox>();

	auto& tb = b->getComponent<CTransform>();
	auto& bbb = b->getComponent<CBoundingBox>();

	float overlapX = (bba.halfSize.x + bbb.halfSize.x) - abs(tb.position.x - ta.position.x);
	float overlapY = (bba.halfSize.y + bbb.halfSize.y) - abs(tb.position.y - ta.position.y);

	return Vector2(overlapX, overlapY);
}

Vector2 Physics::GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
	if (!a->hasComponent<CBoundingBox>() || !b->hasComponent<CBoundingBox>()) return Vector2(0, 0);

	auto& ta = a->getComponent<CTransform>();
	auto& bba = a->getComponent<CBoundingBox>();

	auto& tb = b->getComponent<CTransform>();
	auto& bbb = b->getComponent<CBoundingBox>();

	float overlapX = (bba.halfSize.x + bbb.halfSize.x) - abs(tb.prevPosition.x - ta.prevPosition.x);
	float overlapY = (bba.halfSize.y + bbb.halfSize.y) - abs(tb.prevPosition.y - ta.prevPosition.y);

	return Vector2(overlapX, overlapY);
}

bool Physics::isColliding(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
	Vector2 overlap = GetOverlap(a, b);

	return (overlap.x > 0 && overlap.y > 0);
}