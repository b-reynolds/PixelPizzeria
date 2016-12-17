#pragma once
#include "Agent.h"
#include "CUSSit.h"
#include "CUSLeave.h"
#include "Simulation.h"
#include "CUSSpawn.h"
#include "CUSEat.h"

class Rat;

class Customer : public Agent
{

private:

	const std::string contentDirectory = "Assets/Agent/Customers/";

	static int count;

	std::vector<std::pair<std::string, sf::Sprite&>> bodyParts;
	std::vector<Rat*> rats;

	Map* map;

	CUSState* cusState;

	CUSSit cusSit;
	CUSLeave cusLeave;
	CUSSpawn cusSpawn;
	CUSEat cusEat;

	bool seated;
	bool served;
	bool ready;
	bool hasFood;

	bool initialize();

public:

	Map& getMap() const;

	void rotate(const sf::Vector2f &direction) override;
	void setPosition(const sf::Vector2f &position) override;

	void update(Map &map, std::vector<Rat*> &rats);
	void draw(sf::RenderWindow &window) override;
	void changeState(CUSState &state);

	sf::Vector2f getPosition() const override;
	sf::Vector2i getTilePosition() const override;

	sf::FloatRect getGlobalBounds() const override;

	std::vector<Rat*>& getRats();

	void setHasFood(const bool &state);
	bool isEating() const;

	void setSeated(const bool &state);
	bool isSeated() const;

	void setServed(const bool &state);
	bool isServed() const;

	void setReady(const bool &ready);
	bool isReady() const;

	std::vector<std::pair<std::string, sf::Sprite&>>& getBodyParts();

	CUSState& getSpawnState();
	CUSState& getSitState();
	CUSState& getEatState();
	CUSState& getLeaveState();

	Customer();
	~Customer();

};

