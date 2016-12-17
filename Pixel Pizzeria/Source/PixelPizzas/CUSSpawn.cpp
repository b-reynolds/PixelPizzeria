#include "CUSSpawn.h"
#include "Map.h"
#include "Customer.h"

std::string CUSSpawn::stateName = "Spawning";

bool CUSSpawn::spawn(Customer& customer)
{
	Map* map = &customer.getMap();
	sf::Vector2i spawnPoint = map->findID(map->TILE_ENTRANCE);
	if (spawnPoint != sf::Vector2i(-1, -1))
	{
		customer.setPosition(Map::tileToWorld(spawnPoint));
		customer.setActive(true);
		return true;
	}
	return false;
}

void CUSSpawn::enter(Customer& customer)
{
	customer.setStateName(stateName);
	printf("%s Entered State: %s\n", customer.getInfo().c_str(), stateName.c_str());
}

void CUSSpawn::update(Customer& customer)
{
	if (spawn(customer))
	{
		customer.changeState(customer.getSitState());
	}
}

void CUSSpawn::exit(Customer& customer)
{
	printf("%s Exited State: %s\n", customer.getInfo().c_str(), stateName.c_str());
}
