#include "CUSSit.h"
#include "PathFinder.h"
#include "Customer.h"
#include "Random.h"

std::string CUSSit::stateName = "Sitting";

void CUSSit::enter(Customer& customer)
{
	customer.setStateName(stateName);
	printf("%s Entered State: %s\n", customer.getInfo().c_str(), stateName.c_str());
}

void CUSSit::update(Customer& customer)
{
	if(customer.isEating())
	{
		customer.changeState(customer.getEatState());
		return;
	}
	
	if(!hasFoundChair)
	{
		Map* map = &customer.getMap();
		chairPosition = map->findID(map->TILE_CHAIR);
		if (chairPosition != sf::Vector2i(-1, -1))
		{
			customer.setPath(PathFinder::getInstance()->findPath(*map, map->worldToTile(customer.getPosition()), chairPosition));
			map->setID(chairPosition, map->TILE_CHAIR_TAKEN);
			hasFoundChair = true;
		}
		return;
	}

	if(!customer.getPath().empty())
	{
		customer.followPath(customer.getMap());
		return;
	}

	if (!customer.isSeated())
	{
		Map* map = &customer.getMap();
		Agent::faceTile(customer, *map, map->TILE_TABLE);
		customer.setSeated(true);
		return;
	}

	customer.setReady(true);

}

void CUSSit::exit(Customer& customer)
{
	printf("%s Exited State: %s\n", customer.getInfo().c_str(), stateName.c_str());
}
