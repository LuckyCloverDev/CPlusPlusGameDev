#pragma once

#include "Vector2.hpp"

struct Intersect { bool result; Vector2 position; };

class Line
{
	Vector2 point_1 = Vector2(0, 0);
	Vector2 point_2 = Vector2(0, 0);
public:
	Line() {}
	Line(Vector2 point) : point_1(point), point_2(point) {}
	Line(Vector2 a, Vector2 b) : point_1(a), point_2(b) {}
	Line(float ax, float ay, float bx, float by) : point_1(ax, ay), point_2(bx, by) {}

	Intersect getIntersection(Line line);
	Intersect getIntersection(Vector2 a, Vector2 b);
};