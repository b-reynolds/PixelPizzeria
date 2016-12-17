#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace sf {
	class RenderWindow;
	class Color;
}

class DebugUtil
{

public:

	static void drawLine(sf::RenderWindow &window, const sf::Vector2f &a, const sf::Vector2f &b, const sf::Color &colour);
	static void drawVertex(sf::RenderWindow &window, const sf::Vector2f &position, const sf::Color &colour);
	static void drawCircle(sf::RenderWindow &window, const sf::Vector2f &position, const float &radius, const sf::Color &colour);
	static void drawRect(sf::RenderWindow &window, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &colour);
	static void drawRect(sf::RenderWindow &window, const sf::FloatRect &rect, const sf::Color &colour);

};

