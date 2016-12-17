#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Map
{

private:

	const std::string contentDirectory = "Assets/Map/Tiles/";

	sf::Texture txtrFloorCarpet;
	sf::Texture txtrKitchenFloor;
	sf::Texture txtrKitchenCounter;
	sf::Texture txtrWall;
	sf::Texture txtrChair;
	sf::Texture txtrTable;
	sf::Texture txtrTablePizza;
	sf::Texture txtrWallPizza;
	sf::Texture txtrWallClipboard;
	sf::Texture txtrWallWorkSurface;

	sf::Sprite currentTile;

	std::vector<std::vector<int>> map;

	bool initialize();

public:

	static const int BORDER_SIZE = 32;
	static const int TILE_SIZE = 48;
	static const int SIZE_X = 18;
	static const int SIZE_Y = 12;

	const int TILE_FLOOR_CARPET = 0;
	const int TILE_CHAIR = 1;
	const int TILE_ENTRANCE = 2;
	const int TILE_EXIT = 3;
	const int TILE_WAITER_ENTRANCE = 4;
	const int TILE_CHEF_ENTRANCE = 5;
	const int TILE_ORDER_DROPOFF = 6;
	const int TILE_ORDER_DROPOFF_CHEF = 7;
	const int TILE_COOK = 8;
	const int TILE_ORDER_DONE_CHEF = 9;
	const int TILE_ORDER_DONE_WAITER = 10;
	const int TILE_FLOOR_KITCHEN = 11;
	const int TILE_KITCHEN_COUNTER = 91;
	const int TILE_WALL_WORK_SURFACE = 92;
	const int TILE_WALL_CLIPBOARD = 93;
	const int TILE_WALL_PIZZA = 94;
	const int TILE_TABLE_PIZZA = 95;
	const int TILE_FLOOR_TAKEN = 96;
	const int TILE_CHAIR_TAKEN = 97;
	const int TILE_TABLE = 98;
	const int TILE_WALL = 99;

	Map();

	void draw(sf::RenderWindow &window);

	void setMap(const std::vector<std::vector<int>> &map);
	void setID(const sf::Vector2i &position, const int &id);

	static sf::Vector2i worldToTile(const sf::Vector2f &position);
	static sf::Vector2f tileToWorld(const sf::Vector2i &position);

	sf::Vector2i findID(const int &id);

	bool isWithinBounds(const sf::Vector2i &position) const;

	bool isTraversable(const sf::Vector2i &position);

	int getID(const sf::Vector2i &position) const;

	sf::Vector2i getSize() const;

	~Map();

};

