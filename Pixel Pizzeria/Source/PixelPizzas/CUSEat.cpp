#include "CUSEat.h"
#include "Customer.h"
#include <cstdio>
#include "Random.h"

std::string CUSEat::stateName = "Eating";

void CUSEat::enter(Customer& customer)
{
	tmrWait.setInterval(Random::getInstance()->getRandomInt(5000, 15000));
	tmrWait.reset();
	customer.setStateName(stateName);
	printf("%s Entered State: %s\n", customer.getInfo().c_str(), stateName.c_str());
}

void CUSEat::update(Customer& customer)
{
	std::vector<Rat*> rats = customer.getRats();
	for (auto & rat : rats)
	{
		if (customer.intersects(rat->getGlobalBounds()))
		{
			customer.setSatisfaction(0);
			customer.setSpeed(500);
			Map* map = &customer.getMap();
			sf::Vector2i tablePosition = Agent::getNeighbourTile(customer, *map, map->TILE_TABLE_PIZZA);
			map->setID(tablePosition, map->TILE_TABLE);
			customer.changeState(customer.getLeaveState());
			return;
		}
	}

	if(tmrWait.hasElapsed())
	{
		Map* map = &customer.getMap();
		sf::Vector2i tablePosition = Agent::getNeighbourTile(customer, *map, map->TILE_TABLE_PIZZA);
		map->setID(tablePosition, map->TILE_TABLE);
		customer.changeState(customer.getLeaveState());
	}
}

void CUSEat::exit(Customer& customer)
{
	printf("%s Exited State: %s\n", customer.getInfo().c_str(), stateName.c_str());
}
