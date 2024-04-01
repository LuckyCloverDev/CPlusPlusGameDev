#include "Line.hpp"

Intersect Line::getIntersection(Line line)
{
	Vector2 r = point_2 - point_1;
	Vector2 s = line.point_2 - line.point_1;

	float rxs = r.crossProduct(s);
	Vector2 cma = line.point_1 - point_1;

	float t = cma.crossProduct(s) / rxs;
	float u = cma.crossProduct(r) / rxs;

	if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
	{
		return { true, Vector2(point_1.x + t * r.x, point_1.x + t * r.y) };
	}
	return { false, Vector2(0, 0) };
}

Intersect Line::getIntersection(Vector2 a, Vector2 b)
{
	Vector2 r = point_2 - point_1;
	Vector2 s = a - b;

	float rxs = r.crossProduct(s);
	Vector2 cma = a - point_1;

	float t = cma.crossProduct(s) / rxs;
	float u = cma.crossProduct(r) / rxs;

	if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
	{
		return { true, Vector2(point_1.x + t * r.x, point_1.x + t * r.y) };
	}
	return { false, Vector2(0, 0) };
}