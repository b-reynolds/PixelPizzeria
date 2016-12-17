#include "WTRCollectOrder.h"
#include "Waiter.h"
#include "PathFinder.h"
#include "Vector.h"
#include "Random.h"

std::string WTRCollectOrder::stateName = "Collecting Order";

void WTRCollectOrder::enter(Waiter& waiter)
{
	tmrWait.setInterval(Random::getInstance()->getRandomInt(1000, 3000));
	Map* map = &waiter.getMap();
	waiter.setPath(PathFinder::getInstance()->findPath(*map, waiter.getTilePosition(), map->findID(map->TILE_ORDER_DONE_WAITER)));
	haveCollectedOrder = false;
	waiter.setStateName(stateName);
	printf("%s Entered State: %s\n", waiter.getInfo().c_str(), stateName.c_str());
}

void WTRCollectOrder::update(Waiter& waiter)
{

	if(haveCollectedOrder)
	{
		if(tmrWait.hasElapsed())
		{
			waiter.changeState(waiter.getServeOrderState());
		}
		return;
	}

	if(!waiter.getPath().empty())
	{
		waiter.followPath(waiter.getMap());
		return;
	}

	std::deque<Order>* orders = &waiter.getOrders();
	for(auto i = (int)orders->size() - 1; i >= 0; --i)
	{
		Order* order = &orders->at(i);
		if(order->getID() == waiter.getCurrentOrder())
		{
			waiter.setCustomer(*order->getCustomer());

			Map* map = &waiter.getMap();

			sf::Vector2i tablePosition = Agent::getNeighbourTile(waiter, *map, map->TILE_WALL);
			if (tablePosition == sf::Vector2i(-1, -1))
			{
				tablePosition = Agent::getNeighbourTile(waiter, *map, map->TILE_WALL_PIZZA);
			}

			waiter.rotate(Vector::normalize(Map::tileToWorld(tablePosition) - waiter.getPosition()));

			int pizzaCount = 0;
			for(auto j = (int)orders->size() - 1; j >= 0; --j)
			{
				if(orders->at(j).isReady())
				{
					pizzaCount++;
				}
			}

			if(pizzaCount == 1)
			{
				map->setID(tablePosition, map->TILE_KITCHEN_COUNTER);
			}

			orders->erase(orders->begin() + i);

			waiter.setHoldingPizza(true);

			haveCollectedOrder = true;
			tmrWait.reset();
			return;
		}
	}
}

void WTRCollectOrder::exit(Waiter& waiter)
{
	printf("%s Exited State: %s\n", waiter.getInfo().c_str(), stateName.c_str());
}
