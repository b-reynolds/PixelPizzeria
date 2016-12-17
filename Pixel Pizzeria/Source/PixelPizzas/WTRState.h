#pragma once

class Waiter;

class WTRState
{

public:

	virtual void enter(Waiter &waiter) = 0;
	virtual void update(Waiter &waiter) = 0;
	virtual void exit(Waiter &waiter) = 0;

	virtual ~WTRState() {}

};

