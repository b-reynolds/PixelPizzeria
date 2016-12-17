#pragma once
#include <random>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Timer.h"
#include "Customer.h"
#include "Waiter.h"
#include "Map.h"
#include "Chef.h"
#include "Order.h"
#include "AgentInfoPanel.h"
#include "Rat.h"

class Simulation
{

private:

	AgentInfoPanel infoPanel;

	Timer tmrSpawner = Timer(250);

	std::vector<Waiter*> waiters;
	std::deque<Customer*> customers;
	std::vector<Chef*> chefs;
	std::vector<Rat*> rats;

	std::deque<Order> orders;

	Map map;

	void update(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);

	static bool isPointWithinRect(const sf::Vector2i &point, const sf::FloatRect &rect);

	sf::Sprite sprSelected;
	sf::Sprite sprBackground;
	sf::Texture txtrBackground;
	

public:

	static float deltaTime;

	void run(const float &deltaTime, sf::RenderWindow &window);

	Simulation();
	~Simulation();

};