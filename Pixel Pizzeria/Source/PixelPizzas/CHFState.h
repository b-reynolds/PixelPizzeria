#pragma once

class Chef;
class Customer;
class Map;

class CHFState
{

public:

	virtual void enter(Chef &chef) = 0;
	virtual void update(Chef &chef) = 0;
	virtual void exit(Chef &chef) = 0;

	virtual ~CHFState() {}

};

