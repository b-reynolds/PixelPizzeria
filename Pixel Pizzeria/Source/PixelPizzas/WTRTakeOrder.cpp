#include "WTRTakeOrder.h"
#include "PathFinder.h"
#include "Customer.h"
#include "Vector.h"
#include "Waiter.h"
#include "Random.h"

std::string WTRTakeOrder::stateName = "Taking Order";

void WTRTakeOrder::enter(Waiter& waiter)
{
	tmrWait.setInterval(Random::getInstance()->getRandomInt(1000, 2000));
	haveTakenOrder = false;
	waiter.setStateName(stateName);
	printf("%s Entered State: %s\n", waiter.getInfo().c_str(), stateName.c_str());
}

void WTRTakeOrder::update(Waiter& waiter)
{
	if(haveTakenOrder)
	{
		if(tmrWait.hasElapsed())
		{
			waiter.changeState(waiter.getDeliverOrderState());
		}
		return;
	}

	if (waiter.getCustomer() == nullptr)
	{
		std::deque<Customer*>* customers = &waiter.getCustomers();
		for (auto i = (int)customers->size() - 1; i >= 0; --i)
		{
			Customer* customer = customers->at(i);
			if(customer->isSeated() && !customer->isServed() && customer->isReady())
			{
				sf::Vector2i customerPosition = Map::worldToTile(customer->getPosition());
				waiter.setPath(PathFinder::getInstance()->findPath(waiter.getMap(), waiter.getTilePosition(), sf::Vector2i(customerPosition.x - 1, customerPosition.y)));
				customer->setServed(true);
				waiter.setCustomer(*customer);
				break;
			}
		}
		return;
	}

	if (!waiter.getPath().empty())
	{
		waiter.followPath(waiter.getMap());
		return;
	}

	sf::Vector2f direction = Vector::normalize(waiter.getCustomer()->getPosition() - waiter.getPosition());
	waiter.rotate(direction);
	haveTakenOrder = true;
	tmrWait.reset();
}

void WTRTakeOrder::exit(Waiter& waiter)
{
	printf("%s Exited State: %s\n", waiter.getInfo().c_str(), stateName.c_str());
}
