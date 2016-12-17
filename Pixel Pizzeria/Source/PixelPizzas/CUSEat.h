#pragma once
#include "CUSState.h"
#include "Timer.h"
#include <string>

class CUSEat : public CUSState
{

private:

	static std::string stateName;

	Timer tmrWait;

public:

	void enter(Customer& customer) override;
	void update(Customer& customer) override;
	void exit(Customer& customer) override;

};

