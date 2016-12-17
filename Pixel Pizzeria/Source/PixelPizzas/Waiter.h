#pragma once
#include "Agent.h"
#include "WTRState.h"
#include "WTRDeliverOrder.h"
#include "WTRCollectOrder.h"
#include "WTRServeOrder.h"
#include "WTRTakeOrder.h"
#include "WTRSpawn.h"
#include "WTRIdle.h"
#include "Order.h"

class Customer;

class Waiter : public Agent
{

private:

	static int count;

	Map* map;
	std::deque<Order>* orders;
	std::deque<Customer*>* customers;

	WTRState* wtrState;

	WTRSpawn wtrSpawn;
	WTRTakeOrder wtrTakeOrder;
	WTRDeliverOrder wtrDeliverOrder;
	WTRIdle wtrIdle;
	WTRCollectOrder wtrCollectOrder;
	WTRServeOrder wtrServeOrder;

	sf::Texture txtrPizza;
	sf::Sprite sprPizza;

	Customer* customer;
	int currentOrder;
	bool holdingPizza;

	bool initialize();

public:

	void draw(sf::RenderWindow &window) override;
	void update(Map &map, std::deque<Customer*> &customers, std::deque<Order> &orders);

	void changeState(WTRState &state);

	void dropCustomer();

	void setCustomer(Customer &customer);

	void setCurrentOrder(const int &currentOrder);
	void setHoldingPizza(const bool &state);

	Customer* getCustomer() const;
	int getCurrentOrder() const;

	Map& getMap() const;

	std::deque<Order>& getOrders() const;
	std::deque<Customer*>& getCustomers() const;

	WTRState& getSpawnState();
	WTRState& getTakeOrderState();
	WTRState& getDeliverOrderState();
	WTRState& getIdleState();
	WTRState& getCollectOrderState();
	WTRState& getServeOrderState();

	Waiter();
	~Waiter();

};

