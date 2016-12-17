#pragma once
#include "WTRState.h"
#include "Timer.h"
#include <string>

class WTRDeliverOrder : public WTRState
{

private:

	static std::string stateName;

	Timer tmrWait;
	bool haveDeliveredOrder = false;

public:

	void enter(Waiter &waiter) override;
	void update(Waiter &waiter) override;
	void exit(Waiter &waiter) override;

};

