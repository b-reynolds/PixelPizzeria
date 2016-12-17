#include "WTRServeOrder.h"
#include "Waiter.h"
#include "PathFinder.h"
#include "Customer.h"
#include "Waiter.h"
#include "Vector.h"
#include "Random.h"

std::string WTRServeOrder::stateName = "Serving Food";

void WTRServeOrder::enter(Waiter& waiter)
{
	tmrWait.setInterval(Random::getInstance()->getRandomInt(1000, 3000));
	sf::Vector2i customerPosition = waiter.getCustomer()->getTilePosition();
	customerPosition.x -= 1;
	customerPosition.y += 1;
	waiter.setPath(PathFinder::getInstance()->findPath(waiter.getMap(), waiter.getTilePosition(), customerPosition));
	haveServedOrder = false;
	waiter.setStateName(stateName);
	printf("%s Entered State: %s\n", waiter.getInfo().c_str(), stateName.c_str());
}

void WTRServeOrder::update(Waiter& waiter)
{

	if(haveServedOrder)
	{
		if(tmrWait.hasElapsed())
		{
			waiter.changeState(waiter.getIdleState());
		}
		return;
	}

	if(!waiter.getPath().empty())
	{
		waiter.followPath(waiter.getMap());
		return;
	}

	Map* map = &waiter.getMap();
	sf::Vector2i tablePosition = waiter.getNeighbourTile(waiter, *map, map->TILE_TABLE);
	waiter.rotate(Vector::normalize(Map::tileToWorld(tablePosition) - waiter.getPosition()));
	map->setID(tablePosition, map->TILE_TABLE_PIZZA);

	waiter.setHoldingPizza(false);
	waiter.getCustomer()->setHasFood(true);
	float r = waiter.getReliability() / 20;
	float nr = r + 0.5f;
	int fr = (int)nr;
	waiter.getCustomer()->setSatisfaction((int)((waiter.getReliability() / 20) + 0.5f));
	waiter.dropCustomer();
	waiter.setCurrentOrder(0);

	haveServedOrder = true;
	tmrWait.reset();
}

void WTRServeOrder::exit(Waiter& waiter)
{
	printf("%s Exited State: %s\n", waiter.getInfo().c_str(), stateName.c_str());
}
