#pragma once
#include <SFML/Graphics.hpp>
#include "StarRating.h"

class Agent;

class AgentInfoPanel
{

private:

	StarRating starRating;

	sf::Texture txtrPanel;
	sf::Texture txtrAgentDefault;

	sf::Sprite sprPanel;
	sf::Sprite sprAgent;

	std::vector<std::pair<std::string, sf::Sprite&>>* bodyParts;

	sf::RectangleShape rectHitbox;

	sf::Font fntDefault;

	sf::Text txtNameHeader;
	sf::Text txtName;

	sf::Text txtSatisfactionHeader;

	sf::Text txtStateHeader;
	sf::Text txtState;

	sf::Text txtPizzaHeader;
	sf::Text txtPizza;

	sf::Text txtReliabilityHeader;
	sf::Text txtReliability;


	Agent* agent;

	static void centerTextOrigin(sf::Text &text);

	void repositionElements();

public:

	void setAgent(Agent* agent);
	Agent* getAgent() const;

	void draw(sf::RenderWindow &window);
	void update();

	AgentInfoPanel();
	~AgentInfoPanel();

};

