#include <SFML/System/Vector2.hpp>
#include "WTRSpawn.h"
#include "Waiter.h"
#include "Map.h"

std::string WTRSpawn::stateName = "Spawn";

bool WTRSpawn::spawn(Waiter& waiter)
{
	Map* map = &waiter.getMap();
	sf::Vector2i spawnPoint = map->findID(map->TILE_WAITER_ENTRANCE);
	if(spawnPoint != sf::Vector2i(-1, -1))
	{
		waiter.setPosition(Map::tileToWorld(spawnPoint));
		waiter.setActive(true);
		return true;
	}
	return false;
}

void WTRSpawn::enter(Waiter& waiter)
{
	waiter.setStateName(stateName);
	printf("%s Entered State: %s\n", waiter.getInfo().c_str(), stateName.c_str());
}

void WTRSpawn::update(Waiter& waiter)
{
	if (spawn(waiter))
	{
		waiter.changeState(waiter.getIdleState());
	}
}

void WTRSpawn::exit(Waiter& waiter)
{
	printf("%s Exited State: %s\n", waiter.getInfo().c_str(), stateName.c_str());
}
