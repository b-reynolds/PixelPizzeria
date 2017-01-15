#include "Simulation.h"
#include <SFML/Window/Mouse.hpp>
#include "Random.h"

float Simulation::deltaTime = 0.0f;

void Simulation::update(sf::RenderWindow &window)
{

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			bool agentWasSelected = false;

			std::vector<Agent*> agents;
			for(auto & customer : customers)
			{
				agents.push_back(customer);
			}
			for(auto & waiter : waiters)
			{
				agents.push_back(waiter);
			}
			for(auto & chef : chefs)
			{
				agents.push_back(chef);
			}

			// Cycle through all active agents to determine if and which one was clicked
			for(auto& agent : agents)
			{
				if(agent != nullptr)
				{
					sf::FloatRect rectAgentBounds = agent->getGlobalBounds();
					if (isPointWithinRect(mousePosition, rectAgentBounds))
					{
						infoPanel.setAgent(agent);
						agentWasSelected = true;
						break;
					}
				}
			}
			// No agent was selected
			if(!agentWasSelected)
			{
				infoPanel.setAgent(nullptr);
			}
		}
	}

	// If there is less than 14 customers in the shop and the spawn timer has elapsed (random period of time), spawn a new customer
	if (customers.size() < 14 && tmrSpawner.hasElapsed())
	{
		Customer* t = new Customer();
		customers.push_front(t);
		tmrSpawner.setInterval(Random::getInstance()->getRandomInt(0, 5000));
		tmrSpawner.reset();
	}
	infoPanel.update();

	// Update the customers
	for(unsigned int i = 0; i < customers.size(); ++i)
	{
		customers[i]->update(map, rats);
		// If a customer has left the shop and been flagged inactive, delete them from memory.
		if(!customers[i]->isActive())
		{
			if(infoPanel.getAgent() == customers[i])
			{
				infoPanel.setAgent(nullptr);
			}
			delete customers[i];
			customers.erase(customers.begin() + i);
		}
	}

	// Update the waiters
	for(auto& waiter : waiters)
	{
		waiter->update(map, customers, orders);
	}

	// Update the chefs
	for (auto & chef : chefs)
	{
		chef->update(map, orders);
	}

	// Update the rats
	for(auto & rat : rats)
	{
		rat->update();
	}
}

void Simulation::draw(sf::RenderWindow& window)
{
	// Draw all of the game objects
	window.draw(sprBackground);
	for (auto & rat : rats)
	{
		rat->draw(window);
	}
	map.draw(window);
	for (auto& customer : customers)
	{
		customer->draw(window);
	}
	for (auto& waiter : waiters)
	{
		waiter->draw(window);
	}
	for (auto & chef : chefs)
	{
		chef->draw(window);
	}
	infoPanel.draw(window);
}

bool Simulation::isPointWithinRect(const sf::Vector2i& point, const sf::FloatRect& rect)
{
	return point.x >= rect.left && point.x <= rect.left + rect.width && point.y >= rect.top && point.y <= rect.top + rect.height;
}

void Simulation::run(const float& deltaTime, sf::RenderWindow& window)
{
	this->deltaTime = deltaTime;
	update(window);
	draw(window);
}

Simulation::Simulation()
{
	txtrBackground.loadFromFile("Assets/Map/Background.png");
	sprBackground.setTexture(txtrBackground);
	sprBackground.setPosition(Map::BORDER_SIZE, Map::BORDER_SIZE);

	sprSelected.setPosition(sf::Vector2f(928, 32));
	sprSelected.setScale(sf::Vector2f(5, 5));

	for(int i = 0; i < 1; ++i)
	{
		Rat* t = new Rat();
		rats.push_back(t);
	}

	for (int i = 0; i < 3; ++i)
	{
		Waiter* t = new Waiter();
		waiters.push_back(t);
	}

	for (int i = 0; i < 2; ++i)
	{
		Chef* t = new Chef();
		chefs.push_back(t);
	}
}

Simulation::~Simulation()
{
	for(auto& customer : customers)
	{
		delete customer;
	}
	for(auto & waiter : waiters)
	{
		delete waiter;
	}
	for(auto & chef : chefs)
	{
		delete chef;
	}
	for (auto & rat : rats)
	{
		delete rat;
	}
}
