#pragma once
#include "CUSState.h"
#include <string>

class CUSSpawn : public CUSState
{

private:

	static std::string stateName;

	static bool spawn(Customer &customer);

public:


	void enter(Customer& customer) override;
	void update(Customer& customer) override;
	void exit(Customer& customer) override;

};

