#include "Order.h"
#include "Customer.h"

int Order::orderCount = 0;

void Order::setTaken(const bool& state)
{
	taken = state;
}

bool Order::isTaken() const
{
	return taken;
}

void Order::setCooking(const bool& state)
{
	this->cooking = state;
}

bool Order::isCooking() const
{
	return cooking;
}

void Order::setReady(const bool& state)
{
	ready = state;
}

bool Order::isReady() const
{
	return ready;
}

void Order::setCustomer(Customer& customer)
{
	this->customer = &customer;
}

Customer* Order::getCustomer() const
{
	return customer;
}

int Order::getID() const
{
	return id;
}

Order::Order(Customer* customer)
{
	this->customer = customer;
	ready = false;
	taken = false;
	cooking = false;
	orderCount++;
	id = orderCount;
}

Order::~Order()
{
}
