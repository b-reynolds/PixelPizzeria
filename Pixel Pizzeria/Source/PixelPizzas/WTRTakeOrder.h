#pragma once
#include "WTRState.h"
#include "Timer.h"
#include <string>

class WTRTakeOrder : public WTRState
{

private:

	static std::string stateName;

	Timer tmrWait;
	bool haveTakenOrder = false;

public:

	void enter(Waiter &waiter) override;
	void update(Waiter &waiter) override;
	void exit(Waiter &waiter) override;

};

