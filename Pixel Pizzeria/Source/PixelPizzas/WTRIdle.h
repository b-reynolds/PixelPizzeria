#pragma once
#include "WTRState.h"
#include <string>

class WTRIdle : public WTRState
{

private:

	static std::string stateName;

public:

	void enter(Waiter &waiter) override;
	void update(Waiter &waiter) override;
	void exit(Waiter &waiter) override;

};

