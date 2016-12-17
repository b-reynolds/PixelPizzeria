#include "Colours.h"
#include <fstream>
#include <string>
#include <sstream>
#include "Random.h"

Colours* Colours::instance = nullptr;

Colours::Colours()
{
	std::ifstream fileStream;

	fileStream.open("Assets/Data/skintones");

	if (fileStream.is_open())
	{
		for (std::string line; getline(fileStream, line);)
		{
			int count = 0;
			sf::Color colour;

			std::stringstream stringStream(line);

			std::string t;
			while (getline(stringStream, t, ',')) {
				if (count == 0)
				{
					colour.r = stoi(t);
				}
				else if (count == 1)
				{
					colour.g = stoi(t);
				}
				else if (count == 2)
				{
					colour.b = stoi(t);
				}
				else
				{
					break;
				}
				count++;
			}
			skinTones.push_back(colour);
		}
	}

	fileStream.close();

	fileStream.open("Assets/Data/hairtones");

	if (fileStream.is_open())
	{
		for (std::string line; getline(fileStream, line);)
		{
			int count = 0;
			sf::Color colour;

			std::stringstream stringStream(line);

			std::string t;
			while (getline(stringStream, t, ',')) {
				if (count == 0)
				{
					colour.r = stoi(t);
				}
				else if (count == 1)
				{
					colour.g = stoi(t);
				}
				else if (count == 2)
				{
					colour.b = stoi(t);
				}
				else
				{
					break;
				}
				count++;
			}
			hairTones.push_back(colour);
		}
	}

	fileStream.close();
}

Colours* Colours::getInstance()
{
	if(instance == nullptr)
	{
		instance = new Colours();
	}
	return instance;
}

sf::Color Colours::getSkinTone()
{
	Random* random = Random::getInstance();
	return skinTones[random->getRandomInt(0, skinTones.size() - 1)];
}

sf::Color Colours::getHairTone()
{
	Random* random = Random::getInstance();
	return hairTones[random->getRandomInt(0, hairTones.size() - 1)];
}

sf::Color Colours::getRandomColour()
{
	Random* random = Random::getInstance();
	return sf::Color(random->getRandomInt(0, 255), random->getRandomInt(0, 255), random->getRandomInt(0, 255));
}

Colours::~Colours()
{
	delete instance;
}
