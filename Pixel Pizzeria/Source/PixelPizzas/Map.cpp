#include "Map.h"

bool Map::initialize()
{
	if(!txtrFloorCarpet.loadFromFile(contentDirectory + "FloorCarpet.png"))
	{
		return false;
	}
	if(!txtrWall.loadFromFile(contentDirectory + "Wall.png"))
	{
		return false;
	}
	if(!txtrChair.loadFromFile(contentDirectory + "Chair.png"))
	{
		return false;
	}
	if(!txtrTable.loadFromFile(contentDirectory + "Table.png"))
	{
		return false;
	}
	if(!txtrTablePizza.loadFromFile(contentDirectory + "TablePizza.png"))
	{
		return false;
	}
	if(!txtrWallPizza.loadFromFile(contentDirectory + "WallPizza.png"))
	{
		return false;
	}
	if (!txtrWallClipboard.loadFromFile(contentDirectory + "WallClipboard.png"))
	{
		return false;
	}
	if (!txtrWallWorkSurface.loadFromFile(contentDirectory + "WallWorkSurface.png"))
	{
		return false;
	}
	if(!txtrKitchenFloor.loadFromFile(contentDirectory + "KitchenFloor.png"))
	{
		return false;
	}
	if (!txtrKitchenCounter.loadFromFile(contentDirectory + "KitchenCounter.png"))
	{
		return false;
	}
	return true;
}

Map::Map()
{
	if(!initialize())
	{
		printf("Failed to initialize Map\n");
	}

	//map.resize(SIZE_X, std::vector<int>(SIZE_Y, 0));
	map = std::vector<std::vector<int>>
	{
		{   0, 99,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
		{   2,  0, 0,  0,  1, 98,  0,  1, 98,  0,  1, 98 },
		{  99, 99,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
		{  0,  1, 98,  0,  1, 98,  0,  1, 98,  0,  1, 98 },
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
		{  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
		{  6,  0,  0,  0,  0,  0,  0,  1, 98,  0,  1, 98},
		{ 93, 91, 91, 91, 91,  0,  0,  0,  0,  0,  0,  0 },
		{  7, 11, 11, 11, 91,  0,  0,  0,  0,  0,  0,  0 },
		{ 11, 11, 11, 11, 91,  0,  0,  1, 98,  0,  1, 98 },
		{ 11, 11, 11, 11, 91,  0,  0,  0,  0,  0,  0,  0 },
		{ 11, 11, 11,  9, 91,  10, 0,  0,  0,  0,  0,  0 },
		{ 11, 11, 11, 11, 91,  0,  0,  1, 98,  0,  1, 98 },
		{ 11, 11, 11, 11, 91,  0,  0,  0,  0,  0,  0,  0 },
		{ 11, 11, 11, 11, 91,  0,  0,  0,  0,  0, 99, 99 },
		{ 11, 11, 11,  8, 92,  0,  0,  1, 98,  0,  0,  0 },
		{ 5, 11, 11,  11, 91,  0,  0,  0,  0,  0, 99,  3 },

	};

}

void Map::draw(sf::RenderWindow& window)
{
	for(auto x = 0; x < SIZE_X; ++x)
	{
		for(auto y = 0; y < SIZE_Y; ++y)
		{
			currentTile.setPosition((float)BORDER_SIZE + x * TILE_SIZE, (float)BORDER_SIZE + y * TILE_SIZE);

			if(map[x][y] == TILE_WALL)
			{
				currentTile.setTexture(txtrWall);
				window.draw(currentTile);
			}
			else if(map[x][y] == TILE_CHAIR || map[x][y] == TILE_CHAIR_TAKEN)
			{
				currentTile.setTexture(txtrChair);
				window.draw(currentTile);
			}
			else if(map[x][y] == TILE_TABLE)
			{
				currentTile.setTexture(txtrTable);
				window.draw(currentTile);
			}
			else if(map[x][y] == TILE_TABLE_PIZZA)
			{
				currentTile.setTexture(txtrTablePizza);
				window.draw(currentTile);
			}
			else if(map[x][y] == TILE_WALL_PIZZA)
			{
				currentTile.setTexture(txtrWallPizza);
				window.draw(currentTile);
			}
			else if(map[x][y] == TILE_WALL_CLIPBOARD)
			{
				currentTile.setTexture(txtrWallClipboard);
				window.draw(currentTile);
			}
			else if (map[x][y] == TILE_WALL_WORK_SURFACE)
			{
				currentTile.setTexture(txtrWallWorkSurface);
				window.draw(currentTile);
			}
			else if(map[x][y] == TILE_KITCHEN_COUNTER)
			{
				currentTile.setTexture(txtrKitchenCounter);
				window.draw(currentTile);
			}

		}
	}
}

void Map::setMap(const std::vector<std::vector<int>>& map)
{
	for(int x = 0; x < SIZE_X; ++x)
	{
		for(int y = 0; y < SIZE_Y; ++y)
		{
			this->map[x][y] = map[x][y];
		}
	}
}

void Map::setID(const sf::Vector2i& position, const int& id)
{
	map[position.x][position.y] = id;
}

sf::Vector2i Map::worldToTile(const sf::Vector2f& position)
{
	return sf::Vector2i((position.x - Map::BORDER_SIZE) / Map::TILE_SIZE, (position.y - Map::BORDER_SIZE) / Map::TILE_SIZE);
}

sf::Vector2f Map::tileToWorld(const sf::Vector2i& position)
{
	return sf::Vector2f(position.x * TILE_SIZE + BORDER_SIZE + TILE_SIZE / 2, position.y * TILE_SIZE + BORDER_SIZE + TILE_SIZE / 2);
}

sf::Vector2i Map::findID(const int& id)
{
	for (auto x = 0; x < SIZE_X; ++x)
	{
		for (auto y = 0; y < SIZE_Y; ++y)
		{
			if (map[x][y] == id)
			{
				return sf::Vector2i(x, y);
			}
		}
	}
	return sf::Vector2i(-1, -1);
}

bool Map::isWithinBounds(const sf::Vector2i& position) const
{
	return position.x >= 0 && position.x < SIZE_X && position.y >= 0 && position.y < SIZE_Y;
}

bool Map::isTraversable(const sf::Vector2i& position)
{
	return map[position.x][position.y] < 90;
}

int Map::getID(const sf::Vector2i& position) const
{
	return map[position.x][position.y];
}

sf::Vector2i Map::getSize() const
{
	return sf::Vector2i(SIZE_X, SIZE_Y);
}

Map::~Map()
{
}
