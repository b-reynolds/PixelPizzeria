#pragma once
#include "CHFState.h"
#include <string>

class CHFSpawn : public CHFState
{

private:

	static std::string stateName;

	static bool spawn(Chef &chef);

public:

	void enter(Chef &chef) override;
	void update(Chef &chef) override;
	void exit(Chef &chef) override;

};

