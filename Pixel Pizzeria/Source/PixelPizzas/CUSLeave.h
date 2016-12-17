#pragma once
#include "CUSState.h"
#include <string>

class CUSLeave : public CUSState
{

private:

	static std::string stateName;

public:

	void enter(Customer& customer) override;
	void update(Customer& customer) override;
	void exit(Customer& customer) override;

};

