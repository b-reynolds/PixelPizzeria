#include "Waiter.h"
#include "Simulation.h"
#include "WTRDeliverOrder.h"
#include "Random.h"

int Waiter::count = 0;

bool Waiter::initialize()
{
	int randomTexture = 0;
	if (gender == 0)
	{
		randomTexture = Random::getInstance()->getRandomInt(1, 3);
	}
	else
	{
		randomTexture = Random::getInstance()->getRandomInt(4, 6);
	}
	if (!txtrAgent.loadFromFile("Assets/Agent/Waiters/" + std::to_string(randomTexture) + ".png"))
	{
		return false;
	}
	sprAgent.setTexture(txtrAgent);
	if(!txtrPizza.loadFromFile("Assets/Agent/General/Pizza.png"))
	{
		return false;
	}
	sprPizza.setTexture(txtrPizza);
	return true;
}

void Waiter::draw(sf::RenderWindow &window)
{
	if (active)
	{
		window.draw(sprAgent);
		if (holdingPizza)
		{
			window.draw(sprPizza);
		}
	}
}

void Waiter::update(Map& map, std::deque<Customer*> &customers, std::deque<Order> &orders)
{
	this->map = &map;
	this->customers = &customers;
	this->orders = &orders;

	if (holdingPizza)
	{
		sprPizza.setPosition(sprAgent.getPosition());
		sprPizza.setRotation(sprAgent.getRotation());
		sprPizza.setOrigin(sprAgent.getOrigin());
	}

	wtrState->update(*this);
}

void Waiter::changeState(WTRState &state)
{
	if(wtrState != nullptr)
	{
		wtrState->exit(*this);
	}
	wtrState = &state;
	wtrState->enter(*this);
}

void Waiter::dropCustomer()
{
	customer = nullptr;
}

void Waiter::setCustomer(Customer &customer)
{
	this->customer = &customer;
}

void Waiter::setCurrentOrder(const int &currentOrder)
{
	this->currentOrder = currentOrder;
}

void Waiter::setHoldingPizza(const bool &state)
{
	holdingPizza = state;
}

int Waiter::getCurrentOrder() const
{
	return currentOrder;
}

std::deque<Order>& Waiter::getOrders() const
{
	return *orders;
}

std::deque<Customer*>& Waiter::getCustomers() const
{
	return *customers;
}

Map& Waiter::getMap() const
{
	return *map;
}

WTRState& Waiter::getSpawnState()
{
	return wtrSpawn;
}

WTRState& Waiter::getTakeOrderState()
{
	return wtrTakeOrder;
}

WTRState& Waiter::getDeliverOrderState()
{
	return wtrDeliverOrder;
}

WTRState& Waiter::getIdleState()
{
	return wtrIdle;
}

WTRState& Waiter::getCollectOrderState()
{
	return wtrCollectOrder;
}

WTRState& Waiter::getServeOrderState()
{
	return wtrServeOrder;
}

Customer* Waiter::getCustomer() const
{
	return customer;
}

Waiter::Waiter()
{
	wtrState = nullptr;

	holdingPizza = false;

	count++;
	id = count;

	reliability = Random::getInstance()->getRandomInt(30, 100);

	agentType = "Waiter";

	if (!initialize())
	{
		printf("Error: failed to initialize Chef (%i)\n", id);
	}

	changeState(getSpawnState());
}

Waiter::~Waiter()
{

}
