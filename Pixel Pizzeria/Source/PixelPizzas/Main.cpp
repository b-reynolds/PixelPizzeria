#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "DebugUtil.h"
#include "windows.h"

const int WIN_X = 1216;
const int WIN_Y = 640;
const char WIN_TITLE[] = "Pixel Pizzeria";

sf::Color getRandomColour()
{
	std::uniform_int_distribution<int> ud(0, 255);
	std::random_device rd;
	return sf::Color(ud(rd), ud(rd), ud(rd));
}

int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	sf::Clock deltaClock;
	float deltaTime = 0.0f;

	Simulation simulation;

	sf::RenderWindow window(sf::VideoMode(WIN_X, WIN_Y), WIN_TITLE, sf::Style::Close);
	sf::Image icon;
	icon.loadFromFile("Assets/icon.png");
	window.setIcon(32, 32, icon.getPixelsPtr());

	while(window.isOpen())
	{
		window.clear();

		simulation.run(deltaTime, window);

		DebugUtil::drawRect(window, sf::Vector2f(0, 0), sf::Vector2f(Map::BORDER_SIZE, WIN_Y), sf::Color::Black);
		DebugUtil::drawRect(window, sf::Vector2f(Map::BORDER_SIZE + Map::SIZE_X * Map::TILE_SIZE, 0), sf::Vector2f(Map::BORDER_SIZE, WIN_Y), sf::Color::Black);
		DebugUtil::drawRect(window, sf::Vector2f(Map::BORDER_SIZE, 0), sf::Vector2f(Map::SIZE_X * Map::TILE_SIZE, Map::BORDER_SIZE), sf::Color::Black);
		DebugUtil::drawRect(window, sf::Vector2f(Map::BORDER_SIZE, WIN_Y - Map::BORDER_SIZE), sf::Vector2f(Map::SIZE_X * Map::TILE_SIZE, Map::BORDER_SIZE), sf::Color::Black);

		window.display();

		deltaTime = deltaClock.restart().asSeconds();
	}

	return 0;
}