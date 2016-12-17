#pragma once
#include <SFML/Graphics/Color.hpp>
#include <vector>

class Colours
{

private:

	Colours();
	static Colours* instance;

	std::vector<sf::Color> skinTones;
	std::vector<sf::Color> hairTones;

public:

	static Colours* getInstance();

	sf::Color getSkinTone();
	sf::Color getHairTone();
	static sf::Color getRandomColour();

	~Colours();

};

