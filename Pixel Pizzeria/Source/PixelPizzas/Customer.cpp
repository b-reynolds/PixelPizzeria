#include "Customer.h"
#include "CUSEat.h"
#include "Random.h"
#include "Colours.h"

int Customer::count = 0;

bool Customer::initialize()
{
	std::pair<int, int> maleHairs(1, 6);
	std::pair<int, int> femaleHairs(1, 4);
	std::pair<int, int> hats(1, 4);
	std::pair<int, int> mouths(1, 4);

	Random* random = Random::getInstance();
	Colours* colours = Colours::getInstance();

	std::string genderPrefix = gender == 0 ? "m" : "f";

	txtrHead.loadFromFile("Assets/Agent/Parts/head.png");
	txtrMouth.loadFromFile("Assets/Agent/Parts/mouth" + std::to_string(random->getRandomInt(mouths)) + ".png");
	txtrEyes.loadFromFile("Assets/Agent/Parts/" + genderPrefix + "eyes.png");
	txtrHair.loadFromFile("Assets/Agent/Parts/" + genderPrefix + "hair" + std::to_string(random->getRandomInt(gender ? femaleHairs : maleHairs)) + ".png");
	txtrHat.loadFromFile("Assets/Agent/Parts/hat" + std::to_string(random->getRandomInt(hats)) + ".png");
	txtrBody.loadFromFile("Assets/Agent/Parts/body.png");
	txtrHands.loadFromFile("Assets/Agent/Parts/arms.png");
	txtrLegs.loadFromFile("Assets/Agent/Parts/" + genderPrefix + "legs.png");
	txtrFeet.loadFromFile("Assets/Agent/Parts/feet.png");

	sprHead.setTexture(txtrHead);
	sprMouth.setTexture(txtrMouth);
	sprEyes.setTexture(txtrEyes);
	sprHair.setTexture(txtrHair);
	sprHat.setTexture(txtrHat);
	sprBody.setTexture(txtrBody);
	sprHands.setTexture(txtrHands);
	sprLegs.setTexture(txtrLegs);
	sprFeet.setTexture(txtrFeet);

	sf::Color skinColour = colours->getSkinTone();
	sf::Color hairColour = colours->getHairTone();

	sprHead.setColor(skinColour);
	sprHands.setColor(skinColour);
	sprHair.setColor(colours->getHairTone());
	sprHat.setColor(random->getRandomInt(1, 4) == 1 ? Colours::getRandomColour() : sf::Color(0, 0, 0, 0));
	sprBody.setColor(Colours::getRandomColour());
	sprLegs.setColor(Colours::getRandomColour());
	sprFeet.setColor(Colours::getRandomColour());

	bodyParts.push_back(std::pair<std::string, sf::Sprite&>("Head", sprHead));
	bodyParts.push_back(std::pair<std::string, sf::Sprite&>("Mouth", sprMouth));
	bodyParts.push_back(std::pair<std::string, sf::Sprite&>("Eyes", sprEyes));
	bodyParts.push_back(std::pair<std::string, sf::Sprite&>("Hair", sprHair));
	bodyParts.push_back(std::pair<std::string, sf::Sprite&>("Hat", sprHat));
	bodyParts.push_back(std::pair<std::string, sf::Sprite&>("Body", sprBody));
	bodyParts.push_back(std::pair<std::string, sf::Sprite&>("Hands", sprHands));
	bodyParts.push_back(std::pair<std::string, sf::Sprite&>("Legs", sprLegs));
	bodyParts.push_back(std::pair<std::string, sf::Sprite&>("Feet", sprFeet));

	for (auto const& pair : bodyParts)
	{
		pair.second.setOrigin(Map::TILE_SIZE / 2, Map::TILE_SIZE / 2);
	}

	active = true;

	return true;
}

Map& Customer::getMap() const
{
	return *map;
}

void Customer::rotate(const sf::Vector2f& direction)
{
	float desiredRotation = atan2(direction.y, direction.x) * 180 / (float)M_PI - 90;
	for (auto const& pair : bodyParts)
	{
		pair.second.setRotation(desiredRotation);
	}
}

void Customer::setPosition(const sf::Vector2f& position)
{
	for (auto const& pair : bodyParts)
	{
		pair.second.setPosition(position);
	}
}

void Customer::update(Map& map, std::vector<Rat*>& rats)
{
	this->map = &map;
	this->rats = rats;
	cusState->update(*this);
}

void Customer::draw(sf::RenderWindow& window)
{
	if(active)
	{
		for (auto const& pair : bodyParts)
		{
			window.draw(pair.second);
		}
	}
}

void Customer::changeState(CUSState& state)
{
	if(cusState != nullptr)
	{
		cusState->exit(*this);
	}
	cusState = &state;
	cusState->enter(*this);
}

sf::Vector2f Customer::getPosition() const
{
	return bodyParts[0].second.getPosition();
}

sf::Vector2i Customer::getTilePosition() const
{
	return Map::worldToTile(bodyParts[0].second.getPosition());

}

sf::FloatRect Customer::getGlobalBounds() const
{
	return bodyParts[0].second.getGlobalBounds();
}

std::vector<Rat*>& Customer::getRats()
{
	return rats;
}

void Customer::setHasFood(const bool& state)
{
	hasFood = state;
}

bool Customer::isEating() const
{
	return hasFood;
}

void Customer::setSeated(const bool& state)
{
	seated = state;
}

bool Customer::isSeated() const
{
	return seated;
}

void Customer::setServed(const bool& state)
{
	served = state;
}

bool Customer::isServed() const
{
	return served;
}

void Customer::setReady(const bool& ready)
{
	this->ready = ready;
}

bool Customer::isReady() const
{
	return ready;
}

std::vector<std::pair<std::string, sf::Sprite&>>& Customer::getBodyParts()
{
	return bodyParts;
}

CUSState& Customer::getSpawnState()
{
	return cusSpawn;
}

CUSState& Customer::getSitState()
{
	return cusSit;
}

CUSState& Customer::getEatState()
{
	return cusEat;
}

CUSState& Customer::getLeaveState()
{
	return cusLeave;
}

Customer::Customer()
{
	cusState = nullptr;

	count++;
	id = count;

	agentType = "Customer";

	if (!initialize())
	{
		printf("Error: failed to initialize Customer\n");
	}

	changeState(getSpawnState());
}

Customer::~Customer()
{

}
