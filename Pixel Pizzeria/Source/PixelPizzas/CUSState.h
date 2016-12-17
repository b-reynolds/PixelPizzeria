#pragma once

class Customer;
class Map;

class CUSState
{

public:

	virtual void enter(Customer &customer) = 0;
	virtual void update(Customer &customer) = 0;
	virtual void exit(Customer &customer) = 0;

	virtual ~CUSState() {}

};

