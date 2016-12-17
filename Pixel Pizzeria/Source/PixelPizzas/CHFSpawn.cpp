#include "CHFSpawn.h"
#include <SFML/System/Vector2.hpp>
#include "Map.h"
#include "Chef.h"

std::string CHFSpawn::stateName = "Spawning";

bool CHFSpawn::spawn(Chef &chef)
{
	Map* map = &chef.getMap();
	sf::Vector2i spawnPoint = map->findID(map->TILE_CHEF_ENTRANCE);
	if (spawnPoint != sf::Vector2i(-1, -1))
	{
		chef.setPosition(map->tileToWorld(spawnPoint));
		chef.setActive(true);
		return true;
	}
	return false;
}

void CHFSpawn::enter(Chef& chef)
{
	chef.setStateName(stateName);
	printf("%s Entered State: %s\n", chef.getInfo().c_str(), stateName.c_str());
}

void CHFSpawn::update(Chef& chef)
{
	if (spawn(chef))
	{
		chef.changeState(chef.getCollectOrderState());
	}
}

void CHFSpawn::exit(Chef& chef)
{
	printf("%s Exited State: %s\n", chef.getInfo().c_str(), stateName.c_str());
}
