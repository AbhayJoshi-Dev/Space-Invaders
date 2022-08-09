#include <cmath>

#include "Vector.h"

Vector::Vector(float x, float y)
	: m_x(x), m_y(y)
{

}

void Vector::SetX(float value)
{
	m_x = value;
}

void Vector::SetY(float value)
{
	m_y = value;
}

float Vector::GetX() const
{
	return m_x;
}

float Vector::GetY() const
{
	return m_y;
}

void Vector::SetAngle(float angle)
{
	float length = GetLength();
	m_x = std::cos(angle) * length;
	m_y = std::sin(angle) * length;
}

float Vector::GetAngle() const
{
	return std::atan2(m_y, m_x);
}

void Vector::SetLength(float len)
{
	float angle = GetAngle();
	m_x = std::cos(angle) * len;
	m_y = std::sin(angle) * len;
}

float Vector::GetLength() const
{
	return std::sqrt(m_x * m_x + m_y * m_y);
}

void Vector::AddTo(const Vector& v)
{
	m_x += v.m_x;
	m_y += v.m_y;
}

void Vector::SubTo(const Vector& v)
{
	m_x -= v.m_x;
	m_y -= v.m_y;
}

void Vector::Scale(float factor)
{
	m_x *= factor;
	m_y *= factor;
}

void Vector::Scale(float x, float y)
{
	m_x *= x;
	m_y *= y;
}

float Vector::Dot(const Vector& other) const
{
	return (m_x * other.m_x + m_y * other.m_y);
}

Vector& Vector::Unitize()
{
	auto mag = GetLength();
	if (mag != 0)
	{
		m_x /= mag;
		m_y /= mag;
	}
	return *this;
}

Vector Vector::Unit() const
{
	auto mag = GetLength();
	if (mag == 0)
	{
		return Vector();
	}
	else
	{
		return Vector(m_x / mag, m_y / mag);
	}
}

Vector Vector::operator+(const Vector& other) const
{
	return Vector(m_x + other.m_x, m_y + other.m_y);
}

Vector Vector::operator-(const Vector& other) const
{
	return Vector(m_x - other.m_x, m_y - other.m_y);
}