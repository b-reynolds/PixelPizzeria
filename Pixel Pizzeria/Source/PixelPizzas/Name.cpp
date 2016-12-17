#include "Name.h"
#include "Random.h"
#include <fstream>
#include <string>

Name* Name::instance = nullptr;

Name::Name()
{
	std::ifstream fileStream;

	fileStream.open("Assets/Data/mnames");

	if(fileStream.is_open())
	{
		for(std::string line; getline(fileStream, line);)
		{
			maleNames.push_back(line);
		}
	}

	fileStream.close();

	fileStream.open("Assets/Data/fnames");

	if (fileStream.is_open())
	{
		for (std::string line; getline(fileStream, line);)
		{
			femaleNames.push_back(line);
		}
	}

	fileStream.close();

	fileStream.open("Assets/Data/snames");

	if (fileStream.is_open())
	{
		for (std::string line; getline(fileStream, line);)
		{
			familyNames.push_back(line);
		}
	}

	fileStream.close();

	fileStream.open("Assets/Data/pizzatoppings");

	if (fileStream.is_open())
	{
		for (std::string line; getline(fileStream, line);)
		{
			pizzaToppings.push_back(line);
		}
	}

	fileStream.close();

	fileStream.open("Assets/Data/pizzacrusts");

	if (fileStream.is_open())
	{
		for (std::string line; getline(fileStream, line);)
		{
			pizzaCrustTypes.push_back(line);
		}
	}

	fileStream.close();

}

Name* Name::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Name();
	}
	return instance;
}

std::string Name::getName(int &gender)
{
	Random* random = Random::getInstance();

	std::string firstName = "";
	std::string familyName = "";

	if(gender == 1)
	{
		firstName += maleNames[random->getRandomInt(0, maleNames.size() - 1)];
	}
	else
	{
		firstName += femaleNames[random->getRandomInt(0, femaleNames.size() - 1)];
	}

	familyName = familyNames[random->getRandomInt(0, familyNames.size() - 1)];
	
	return firstName + " " + familyName;
}

std::string Name::getPizza()
{
	Random* random = Random::getInstance();
	std::string pizzaCrust = pizzaCrustTypes[random->getRandomInt(0, pizzaCrustTypes.size() - 1)];
	std::string pizzaTopping = pizzaToppings[random->getRandomInt(0, pizzaToppings.size() - 1)];
	return pizzaCrust + " " + pizzaTopping;
}

Name::~Name()
{
	delete instance;
}
