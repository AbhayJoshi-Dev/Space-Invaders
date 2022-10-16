#pragma once

class Vector
{
public:
	Vector() = default;
	Vector(float x, float y);

	// Returns addition of other and current vector.
	Vector operator+(const Vector& other) const;

	// Returns subtraction of other vector and from current vector.
	Vector operator-(const Vector& other) const;

public:
	// Saves us from having a default constructor.
	float m_x = 0.f;
	float m_y = 0.f;
};