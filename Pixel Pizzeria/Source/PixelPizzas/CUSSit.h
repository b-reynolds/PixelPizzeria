#pragma once
#include "CUSState.h"
#include <string>
#include <SFML/System/Vector2.hpp>

class CUSSit : public CUSState
{

	static std::string stateName;

	sf::Vector2i chairPosition = sf::Vector2i(-1, -1);

	bool hasFoundChair = false;

public:

	void enter(Customer& customer) override;
	void update(Customer& customer) override;
	void exit(Customer& customer) override;

};

