#pragma once
#include "WTRState.h"
#include <string>

class WTRSpawn : public WTRState
{

private:

	static std::string stateName;

	static bool spawn(Waiter &waiter);

public:

	void enter(Waiter &waiter) override;
	void update(Waiter &waiter) override;
	void exit(Waiter &waiter) override;

};

