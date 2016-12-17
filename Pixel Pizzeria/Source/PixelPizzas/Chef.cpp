#include "Chef.h"
#include "Simulation.h"
#include "CHFCollectOrder.h"
#include "Random.h"

int Chef::count = 0;

bool Chef::initialize()
{
	int randomTexture = 0;
	if(gender == 0)
	{
		randomTexture = Random::getInstance()->getRandomInt(1, 1);
	}
	else
	{
		randomTexture = Random::getInstance()->getRandomInt(2, 2);
	}
	if (!txtrAgent.loadFromFile("Assets/Agent/Chefs/" + std::to_string(randomTexture) + ".png"))
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

void Chef::update(Map &map, std::deque<Order> &orders)
{
	this->map = &map;
	this->orders = &orders;

	if(holdingPizza)
	{
		sprPizza.setPosition(sprAgent.getPosition());
		sprPizza.setRotation(sprAgent.getRotation());
		sprPizza.setOrigin(sprAgent.getOrigin());
	}

	chfState->update(*this);
}

void Chef::draw(sf::RenderWindow &window)
{
	window.draw(sprAgent);
	if(holdingPizza)
	{
		window.draw(sprPizza);
	}
}

void Chef::changeState(CHFState &state)
{
	if (chfState != nullptr)
	{
		chfState->exit(*this);
	}
	chfState = &state;
	chfState->enter(*this);
}

void Chef::setHoldingPizza(const bool& state)
{
	holdingPizza = state;
}

void Chef::setOrderID(const int &orderID)
{
	this->orderID = orderID;
}

int Chef::getOrderID() const
{
	return orderID;
}

Map& Chef::getMap() const
{
	return *map;
}

std::deque<Order>& Chef::getOrders() const
{
	return *orders;
}

CHFState& Chef::getSpawnState()
{
	return chfSpawn;
}

CHFState& Chef::getCollectOrderState()
{
	return chfCollectOrder;
}

CHFState& Chef::getCookOrderState()
{
	return chfCookOrder;
}

CHFState& Chef::getServeOrderState()
{
	return chfServeOrder;
}

Chef::Chef()
{
	chfState = nullptr;

	holdingPizza = false;

	count++;
	id = count;

	agentType = "Chef";

	if (!initialize())
	{
		printf("Error: Failed to initialize Customer (%i)\n", id);
	}

	changeState(getSpawnState());
}


Chef::~Chef()
{

}
