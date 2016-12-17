#include "CHFCookOrder.h"
#include "PathFinder.h"
#include "Chef.h"
#include "Vector.h"
#include "Random.h"

std::string CHFCookOrder::stateName = "Cooking";

void CHFCookOrder::enter(Chef& chef)
{
	tmrWait.setInterval(Random::getInstance()->getRandomInt(1000, 3000));
	Map* map = &chef.getMap();
	chef.setPath(PathFinder::getInstance()->findPath(*map, chef.getTilePosition(), map->findID(map->TILE_COOK)));
	haveCooked = false;
	chef.setStateName(stateName);
	printf("%s Entered State: %s\n", chef.getInfo().c_str(), stateName.c_str());
}

void CHFCookOrder::update(Chef& chef)
{
	if(haveCooked)
	{
		if (tmrWait.hasElapsed())
		{
			chef.changeState(chef.getServeOrderState());
		}
		return;
	}

	if(!chef.getPath().empty())
	{
		chef.followPath(chef.getMap());
		return;
	}

	Map* map = &chef.getMap();
	Agent::faceTile(chef, *map, map->TILE_WALL_WORK_SURFACE);

	haveCooked = true;
	tmrWait.reset();
}

void CHFCookOrder::exit(Chef& chef)
{
	printf("%s Exited State: %s\n", chef.getInfo().c_str(), stateName.c_str());
}
