#include "CHFCollectOrder.h"
#include "Order.h"
#include "Chef.h"
#include "PathFinder.h"
#include "Vector.h"
#include "WTRTakeOrder.h"
#include "Random.h"

std::string CHFCollectOrder::stateName = "Collecting Orders";

void CHFCollectOrder::enter(Chef& chef)
{
	tmrWait.setInterval(Random::getInstance()->getRandomInt(1000, 3000));
	Map* map = &chef.getMap();
	chef.setPath(PathFinder::getInstance()->findPath(*map, chef.getTilePosition(), map->findID(map->TILE_ORDER_DROPOFF_CHEF)));
	hasOrder = false;
	chef.setStateName(stateName);
	printf("%s Entered State: %s\n", chef.getInfo().c_str(), stateName.c_str());
}

void CHFCollectOrder::update(Chef& chef)
{
	if (hasOrder)
	{
		if (tmrWait.hasElapsed())
		{
			chef.changeState(chef.getCookOrderState());
		}
		return;
	}

	if(!chef.getPath().empty())
	{
		chef.followPath(chef.getMap());
		return;
	}

	Map* map = &chef.getMap();
	Agent::faceTile(chef, *map, map->TILE_WALL_CLIPBOARD);

	std::deque<Order>* orders = &chef.getOrders();
	for (auto i = (int)orders->size() - 1; i >= 0; --i)
	{
		Order* order = &orders->at(i);
		if (!order->isReady() && !order->isCooking())
		{
			order->setCooking(true);
			chef.setOrderID(order->getID());
			hasOrder = true;
			tmrWait.reset();
			break;
		}
	}
}

void CHFCollectOrder::exit(Chef& chef)
{
	printf("%s Exited State: %s\n", chef.getInfo().c_str(), stateName.c_str());
}
