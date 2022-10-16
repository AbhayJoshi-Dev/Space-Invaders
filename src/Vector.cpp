#include <cmath>

#include "Vector.h"

Vector::Vector(float x, float y)
	: m_x(x), m_y(y)
{

}

Vector Vector::operator+(const Vector& other) const
{
	return Vector(m_x + other.m_x, m_y + other.m_y);
}

Vector Vector::operator-(const Vector& other) const
{
	return Vector(m_x - other.m_x, m_y - other.m_y);
}