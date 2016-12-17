#include "Vector.h"

sf::Vector2f Vector::normalize(const sf::Vector2f& v1)
{
	float l = length(v1);
	if(l != 0)
	{
		return sf::Vector2f(v1.x / l, v1.y / l);
	}
	return v1;
}

sf::Vector2f Vector::lerp(const float& t, const sf::Vector2f& start, const sf::Vector2f& end)
{
	return start + (end - start) * t;
}

float Vector::distance(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return abs(length(v2 - v1));
}

float Vector::length(const sf::Vector2f& v1)
{
	return sqrt(v1.x * v1.x + v1.y * v1.y);
}

sf::Vector2f Vector::limit(const sf::Vector2f& vector, const float& maxLength)
{
	float lengthSquared = vector.x * vector.x + vector.y * vector.y;
	if (lengthSquared > maxLength * maxLength && lengthSquared > 0)
	{
		float ratio = maxLength / (float)sqrt(lengthSquared);
		return sf::Vector2f(vector.x * ratio, vector.y * ratio);
	}
	return sf::Vector2f(0, 0);
}
