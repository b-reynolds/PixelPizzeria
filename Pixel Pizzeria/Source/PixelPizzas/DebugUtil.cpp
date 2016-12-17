#pragma once
#include "DebugUtil.h"
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

void DebugUtil::drawLine(sf::RenderWindow& window, const sf::Vector2f& a, const sf::Vector2f& b, const sf::Color& colour)
{
	sf::Vertex line[] =
	{
		sf::Vertex(a, colour),
		sf::Vertex(b, colour)
	};
	window.draw(line, 2, sf::Lines);
}

void DebugUtil::drawVertex(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Color &colour)
{
	sf::Vertex v(position, colour);
	window.draw(&v, 1, sf::Points);
}

void DebugUtil::drawCircle(sf::RenderWindow& window, const sf::Vector2f& position, const float& radius, const sf::Color& colour)
{
	sf::CircleShape circle(radius);
	sf::FloatRect rectBounds = circle.getGlobalBounds();
	circle.setOrigin(rectBounds.width / 2, rectBounds.height / 2);
	circle.setPosition(position);
	circle.setOutlineColor(colour);
	circle.setOutlineThickness(1);
	circle.setFillColor(sf::Color::Transparent);
	window.draw(circle);
}

void DebugUtil::drawRect(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& colour)
{
	sf::RectangleShape rectangle;
	rectangle.setPosition(position);
	rectangle.setSize(size);
	rectangle.setFillColor(colour);
	window.draw(rectangle);
}

void DebugUtil::drawRect(sf::RenderWindow& window, const sf::FloatRect& rect, const sf::Color& colour)
{
	sf::RectangleShape rectangle;
	rectangle.setPosition(sf::Vector2f(rect.left, rect.top));
	rectangle.setSize(sf::Vector2f(rect.width, rect.height));
	rectangle.setFillColor(colour);
	window.draw(rectangle);
}
