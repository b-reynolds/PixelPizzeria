#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <stack>
#include <queue>
#include <map>

class Map;

class Agent
{

private:

	bool hasRotated;

protected: 

	int gender;

	float randomScale = 1.0f;
	float rspeed = 0.005f;

	std::vector<std::pair<std::string, sf::Sprite&>> bodyParts;

	std::string stateName;
	std::string agentName;
	std::string agentType;
	std::string favouritePizza;

	sf::Texture txtrAgent;
	sf::Sprite sprAgent;

	sf::Texture txtrHat;
	sf::Texture txtrHair;
	sf::Texture txtrHead;
	sf::Texture txtrEyes;
	sf::Texture txtrMouth;
	sf::Texture txtrBody;
	sf::Texture txtrHands;
	sf::Texture txtrLegs;
	sf::Texture txtrFeet;

	sf::Sprite sprHat;
	sf::Sprite sprHair;
	sf::Sprite sprHead;
	sf::Sprite sprEyes;
	sf::Sprite sprMouth;
	sf::Sprite sprBody;
	sf::Sprite sprHands;
	sf::Sprite sprLegs;
	sf::Sprite sprFeet;

	float speed;

	bool togglething = false;

	std::queue<sf::Vector2f> path;

	int id;

	sf::Vector2i previousTile;

	bool active;
	
	int satisfaction;
	float reliability;

public:

	Agent();

	virtual void draw(sf::RenderWindow &window);

	void followPath(Map &map);
	virtual void rotate(const sf::Vector2f &direction);
	void move(const sf::Vector2f &velocity);

	virtual void setPosition(const sf::Vector2f &position);
	void setPath(std::stack<sf::Vector2i>& path);
	void setActive(const bool &state);

	static void faceTile(Agent &agent, Map &map, const unsigned int &tile);
	static sf::Vector2i getNeighbourTile(Agent &agent, Map &map, const unsigned int &tile);

	sf::Vector2f getSize() const;

	virtual sf::Vector2f getPosition() const;
	virtual sf::Vector2i getTilePosition() const;
	std::queue<sf::Vector2f>const & getPath() const;
	std::string getInfo() const;
	virtual sf::FloatRect getGlobalBounds() const;
	sf::Texture& getTexture();
	float getSpeed() const;
	bool isActive() const;

	void setStateName(const std::string &stateName);
	std::string getStateName() const;

	void setSpeed(const float &speed);

	void setAgentName(const std::string &agentName);
	std::string getAgentName() const;

	void setFavouritePizza(const std::string &favouritePizza);
	std::string getFavouritePizza() const;

	std::string getAgentType() const;

	void setSatisfaction(const int &satisfaction);
	int getSatisfaction() const;

	void setReliability(const float &reliability);
	float getReliability() const;

	bool intersects(const sf::FloatRect &rect) const;

	virtual ~Agent();

};

