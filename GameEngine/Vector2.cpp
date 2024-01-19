#include "Vector2.hpp"

Vector2::Vector2()
	: x(0)
	, y(0)
{}

Vector2::Vector2(float val)
    : x(val)
    , y(val)
{}

Vector2::Vector2(float xin, float yin)
    : x(xin)
    , y(yin)
{}

Vector2::Vector2(const Vector2& v)
    : x(v.x)
    , y(v.y)
{}

Vector2::Vector2(const Vector2& v1, const Vector2& v2)
    : x(v1.x + v2.x)
    , y(v1.y + v2.y)
{}

Vector2 Vector2::operator + (const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
Vector2 Vector2::operator - (const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
Vector2 Vector2::operator * (const float& rhs) const { return Vector2(x * rhs, y * rhs); }
Vector2 Vector2::operator / (const float& rhs) const { return Vector2(x / rhs, y / rhs); }

Vector2& Vector2::operator += (const Vector2& rhs) { x += rhs.x; y += rhs.y; return *this; }
Vector2& Vector2::operator -= (const Vector2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
Vector2& Vector2::operator *= (const float& rhs) { x *= rhs; y *= rhs; return *this; }
Vector2& Vector2::operator /= (const float& rhs) { x /= rhs; y /= rhs; return *this; }

bool Vector2::operator == (const Vector2& rhs) { return (abs(x - rhs.x) <= 0.0001 && abs(y - rhs.y) <= 0.0001); }
bool Vector2::operator != (const Vector2& rhs) { return !(abs(x - rhs.x) <= 0.0001 && abs(y - rhs.y) <= 0.0001); }

float Vector2::distance_to(const Vector2& v) const { return sqrtf((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y)); }
float Vector2::distance_to_squared(const Vector2& v) const { return (v.x - x) * (v.x - x) + (v.y - y) * (v.y - y); }

sf::Vector2f Vector2::to_sf_vector() { return sf::Vector2f(this->x, this->y); }

float        Vector2::length()                       const { return sqrtf(x * x + y * y); }
Vector2      Vector2::normalized()                   const { return (Vector2(0, 0) == *this) ? Vector2(0, 0) : (*this / this->distance_to(Vector2(0, 0))); }
Vector2      Vector2::rotate(float degrees, bool radians = false) const
{
	if (!radians)
		degrees = degrees * 3.141592653589793f / 180.f;
	float x2 = cosf(degrees) * x - sinf(degrees) * y;
	float y2 = sinf(degrees) * x + cosf(degrees) * y;
	return Vector2(x2, y2);
}
void         Vector2::print()                        const { printf("(%.2f, %.2f)\n", this->x, this->y); }
float        Vector2::angle_to_rad(const Vector2& v) const { return atan2f(v.y - this->y, v.x - this->x); }
float        Vector2::angle_to_deg(const Vector2& v) const { return atan2f(v.y - this->y, v.x - this->x) / 3.14159265358979323f * 180.f; }
