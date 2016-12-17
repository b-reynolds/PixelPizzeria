#pragma once
#include <SFML/Graphics.hpp>

class Vector {

public:

	static sf::Vector2f normalize(const sf::Vector2f &v1);
	static sf::Vector2f lerp(const float &t, const sf::Vector2f &start, const sf::Vector2f &end);
	static float distance(const sf::Vector2f &v1, const sf::Vector2f &v2);
	static float length(const sf::Vector2f &v1);
	static sf::Vector2f limit(const sf::Vector2f &vector, const float &maxLength);


};

