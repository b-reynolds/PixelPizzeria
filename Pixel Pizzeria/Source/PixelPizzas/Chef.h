#pragma once
#include "Agent.h"
#include "CHFState.h"
#include "CHFCollectOrder.h"
#include "CHFSpawn.h"
#include "CHFCookOrder.h"
#include "CHFServeOrder.h"
#include "Order.h"

class Map;
class Customer;

class Chef : public Agent
{

private:

	static int count;

	Map* map;
	std::deque<Order>* orders;

	CHFState* chfState;

	CHFSpawn chfSpawn;
	CHFCollectOrder chfCollectOrder;
	CHFCookOrder chfCookOrder;
	CHFServeOrder chfServeOrder;

	sf::Texture txtrPizza;
	sf::Sprite sprPizza;

	int orderID;
	bool holdingPizza;

	bool initialize();

public:

	void update(Map &map, std::deque<Order> &orders);
	void draw(sf::RenderWindow &window) override;

	void changeState(CHFState &state);

	void setHoldingPizza(const bool &state);

	void setOrderID(const int &currentOrder);
	int getOrderID() const;

	Map& getMap() const;
	std::deque<Order>& getOrders() const;

	CHFState& getSpawnState();
	CHFState& getCollectOrderState();
	CHFState& getCookOrderState();
	CHFState& getServeOrderState();

	Chef();
	~Chef();

};

