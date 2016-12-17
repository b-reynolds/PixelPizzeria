#pragma once
#include "CHFState.h"
#include "Timer.h"
#include <string>

class CHFCollectOrder : public CHFState
{

private:

	static std::string stateName;

	Timer tmrWait;
	bool hasOrder = false;

public:

	void enter(Chef &chef) override;
	void update(Chef &chef) override;
	void exit(Chef &chef) override;

};

