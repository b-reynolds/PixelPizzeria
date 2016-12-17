#pragma once
#include <vector>

class Name
{

private:

	const std::string contentDirectory = "Assets/Agent/Names/";

	std::vector<std::string> maleNames;
	std::vector<std::string> femaleNames;
	std::vector<std::string> familyNames;
	std::vector<std::string> pizzaToppings;
	std::vector<std::string> pizzaCrustTypes;

	static Name* instance;
	Name();

public:

	static Name* getInstance();

	std::string getName(int &gender);
	std::string getPizza();

	~Name();
};

