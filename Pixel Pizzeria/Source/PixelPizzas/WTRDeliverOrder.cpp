#include "WTRDeliverOrder.h"
#include "PathFinder.h"
#include "Order.h"
#include "Waiter.h"
#include "Random.h"

std::string WTRDeliverOrder::stateName = "Delivering Order";

void WTRDeliverOrder::enter(Waiter& waiter)
{
	tmrWait.setInterval(Random::getInstance()->getRandomInt(1000, 3000));
	Map* map = &waiter.getMap();
	waiter.setPath(PathFinder::getInstance()->findPath(*map, waiter.getTilePosition(), map->findID(map->TILE_ORDER_DROPOFF)));
	haveDeliveredOrder = false;
	waiter.setStateName(stateName);
	printf("%s Entered State: %s\n", waiter.getInfo().c_str(), stateName.c_str());

}

void WTRDeliverOrder::update(Waiter& waiter)
{
	if(haveDeliveredOrder)
	{
		if(tmrWait.hasElapsed())
		{
			waiter.getOrders().push_front(Order(waiter.getCustomer()));
			waiter.dropCustomer();
			waiter.changeState(waiter.getIdleState());
		}
		return;
	}

	if (!waiter.getPath().empty())
	{
		waiter.followPath(waiter.getMap());
		return;
	}

	Map* map = &waiter.getMap();
	Agent::faceTile(waiter, *map, map->TILE_WALL_CLIPBOARD);
	haveDeliveredOrder = true;
	tmrWait.reset();
}

void WTRDeliverOrder::exit(Waiter& waiter)
{
	printf("%s Exited State: %s\n", waiter.getInfo().c_str(), stateName.c_str());
}
