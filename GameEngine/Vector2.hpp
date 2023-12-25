#pragma once

#include <SFML/Graphics.hpp>

class Vector2
{
public:
    float x = 0.f;
    float y = 0.f;

    Vector2();
    Vector2(float val);
    Vector2(float xin, float yin);
    Vector2(const Vector2& v);
    Vector2(const Vector2& v1, const Vector2& v2);

    Vector2 operator + (const Vector2& rhs) const;
    Vector2 operator - (const Vector2& rhs) const;
    Vector2 operator * (const float& rhs) const;
    Vector2 operator / (const float& rhs) const;

    Vector2& operator += (const Vector2& rhs);
    Vector2& operator -= (const Vector2& rhs);
    Vector2& operator *= (const float& rhs);
    Vector2& operator /= (const float& rhs);

    bool operator == (const Vector2& rhs);
    bool operator != (const Vector2& rhs);

    sf::Vector2f to_sf_vector();

    float length() const;
    float distance_to(const Vector2& v) const;
    float distance_to_squared(const Vector2& v) const;
    Vector2 normalized() const;
    void print() const;
    float angle_to_rad(const Vector2& v) const;
    float angle_to_deg(const Vector2& v) const;
};