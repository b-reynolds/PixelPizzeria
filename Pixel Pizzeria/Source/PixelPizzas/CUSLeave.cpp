#include "CUSLeave.h"
#include "Customer.h"
#include "PathFinder.h"

std::string CUSLeave::stateName = "Leaving";

void CUSLeave::enter(Customer& customer)
{
	Map* map = &customer.getMap();
	customer.setPath(PathFinder::getInstance()->findPath(*map, map->worldToTile(customer.getPosition()), map->findID(map->TILE_EXIT)));
	map->setID(customer.getTilePosition(), map->TILE_CHAIR);
	customer.setStateName(stateName);
	printf("%s Entered State: %s\n", customer.getInfo().c_str(), stateName.c_str());
}

void CUSLeave::update(Customer& customer)
{
	if (!customer.getPath().empty())
	{
		customer.followPath(customer.getMap());
		return;
	}
	customer.setActive(false);
}

void CUSLeave::exit(Customer& customer)
{
	printf("%s Exited State: %s\n", customer.getInfo().c_str(), stateName.c_str());
}
