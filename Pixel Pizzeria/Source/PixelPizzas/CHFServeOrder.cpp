#include "CHFServeOrder.h"
#include "Chef.h"
#include "PathFinder.h"
#include "Vector.h"
#include "Random.h"

std::string CHFServeOrder::stateName = "Serving Food";

void CHFServeOrder::enter(Chef& chef)
{
	tmrWait.setInterval(Random::getInstance()->getRandomInt(1000, 3000));
	Map* map = &chef.getMap();
	chef.setPath(PathFinder::getInstance()->findPath(*map, chef.getTilePosition(), map->findID(map->TILE_ORDER_DONE_CHEF)));
	hasServedOrder = false;
	chef.setHoldingPizza(true);
	chef.setStateName(stateName);
	printf("%s Entered State: %s\n", chef.getInfo().c_str(), stateName.c_str());
}

void CHFServeOrder::update(Chef& chef)
{
	if(hasServedOrder)
	{
		if(tmrWait.hasElapsed())
		{
			chef.changeState(chef.getCollectOrderState());
		}
		return;
	}

	if(!chef.getPath().empty())
	{
		chef.followPath(chef.getMap());
		return;
	}

	Map* map = &chef.getMap();

	sf::Vector2i tablePosition = Agent::getNeighbourTile(chef, *map, map->TILE_KITCHEN_COUNTER);
	if(tablePosition == sf::Vector2i(-1, -1))
	{
		tablePosition = Agent::getNeighbourTile(chef, *map, map->TILE_WALL_PIZZA);
	}

	sf::Vector2f direction = Vector::normalize(Map::tileToWorld(tablePosition) - chef.getPosition());

	chef.rotate(direction);
	chef.setHoldingPizza(false);

	map->setID(tablePosition, map->TILE_WALL_PIZZA);

	std::deque<Order>* orders = &chef.getOrders();
	for (auto i = (int)orders->size() - 1; i >= 0; --i)
	{
		Order* order = &orders->at(i);
		if (order->getID() == chef.getOrderID())
		{
			order->setReady(true);
			hasServedOrder = true;
			tmrWait.reset();
			break;
		}
	}
}

void CHFServeOrder::exit(Chef& chef)
{
	printf("%s Exited State: %s\n", chef.getInfo().c_str(), stateName.c_str());
}
