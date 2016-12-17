#include "WTRIdle.h"
#include "Customer.h"

std::string WTRIdle::stateName = "Idle";

void WTRIdle::enter(Waiter &waiter)
{
	waiter.setStateName(stateName);
	printf("%s Entered State: %s\n", waiter.getInfo().c_str(), stateName.c_str());
}

void WTRIdle::update(Waiter &waiter)
{
	std::deque<Order>* orders = &waiter.getOrders();

	for(auto i = (int)orders->size() - 1; i >= 0; --i)
	{
		Order* order = &orders->at(i);
		if(order->isReady() && !order->isTaken())
		{
			order->setTaken(true);
			waiter.setCurrentOrder(order->getID());
			waiter.changeState(waiter.getCollectOrderState());
			return;
		}
	}

	std::deque<Customer*>* customers = &waiter.getCustomers();


	for(int i = 0; i < customers->size(); ++i)
	{
		if (!customers->at(i)->isServed())
		{
			waiter.changeState(waiter.getTakeOrderState());
			return;
		}
	}

	//for(auto i = (int)customers->size(); --i > 0;)
	//{
	//	if(!customers->at(i)->isServed())
	//	{
	//		waiter.changeState(waiter.getTakeOrderState());
	//		return;
	//	}
	//}
}

void WTRIdle::exit(Waiter &waiter)
{
	printf("%s Exited State: %s\n", waiter.getInfo().c_str(), stateName.c_str());
}
