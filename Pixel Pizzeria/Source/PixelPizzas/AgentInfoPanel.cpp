#include "AgentInfoPanel.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Agent.h"
#include "Customer.h"

void AgentInfoPanel::centerTextOrigin(sf::Text& text)
{
	sf::FloatRect rectText = text.getLocalBounds();
	text.setOrigin(rectText.left + rectText.width / 2.0f, rectText.top + rectText.height / 2.0f);
}

void AgentInfoPanel::repositionElements()
{
	sf::FloatRect rectBounds = sprPanel.getGlobalBounds();
	float panelCenter = rectBounds.left + rectBounds.width / 2.0f;
	float titleSpacing = 3.0f;
	float textSpacing = 1.5f;

	centerTextOrigin(txtNameHeader);
	rectBounds = sprAgent.getGlobalBounds();
	txtNameHeader.setPosition(panelCenter, rectBounds.top + rectBounds.height + txtNameHeader.getGlobalBounds().height * titleSpacing);

	centerTextOrigin(txtName);
	rectBounds = txtNameHeader.getGlobalBounds();
	txtName.setPosition(panelCenter, rectBounds.top + rectBounds.height + txtName.getGlobalBounds().height * textSpacing);

	centerTextOrigin(txtReliabilityHeader);
	rectBounds = txtName.getGlobalBounds();
	txtReliabilityHeader.setPosition(panelCenter, rectBounds.top + rectBounds.height + txtReliabilityHeader.getGlobalBounds().height * titleSpacing);

	centerTextOrigin(txtReliability);
	rectBounds = txtReliabilityHeader.getGlobalBounds();
	txtReliability.setPosition(panelCenter, rectBounds.top + rectBounds.height + txtReliability.getGlobalBounds().height + textSpacing);

	centerTextOrigin(txtSatisfactionHeader);
	rectBounds = txtName.getGlobalBounds();
	txtSatisfactionHeader.setPosition(panelCenter, rectBounds.height + rectBounds.top + txtSatisfactionHeader.getGlobalBounds().height * titleSpacing);

	rectBounds = txtSatisfactionHeader.getGlobalBounds();
	starRating.setPosition(sf::Vector2f(panelCenter, rectBounds.height + rectBounds.top + starRating.getRect().height));

	centerTextOrigin(txtStateHeader);
	std::string agentType = agent->getAgentType();
	if(agentType == "Customer")
	{
		rectBounds = starRating.getRect();
	}
	else if(agentType == "Waiter")
	{
		rectBounds = txtReliability.getGlobalBounds();
	}
	else if(agentType == "Chef")
	{
		rectBounds = txtName.getGlobalBounds();
	}
	txtStateHeader.setPosition(panelCenter, rectBounds.height + rectBounds.top + txtStateHeader.getGlobalBounds().height * titleSpacing);

	centerTextOrigin(txtState);
	rectBounds = txtStateHeader.getGlobalBounds();
	txtState.setPosition(panelCenter, rectBounds.height + rectBounds.top + txtState.getGlobalBounds().height * textSpacing);

	centerTextOrigin(txtPizzaHeader);
	rectBounds = txtState.getGlobalBounds();
	txtPizzaHeader.setPosition(panelCenter, rectBounds.height + rectBounds.top + txtPizzaHeader.getGlobalBounds().height * titleSpacing);

	centerTextOrigin(txtPizza);
	rectBounds = txtPizzaHeader.getGlobalBounds();
	txtPizza.setPosition(panelCenter, rectBounds.height + rectBounds.top + txtPizza.getGlobalBounds().height * textSpacing);

	sf::Vector2f hitBoxPosition(agent->getPosition().x - agent->getSize().x / 2, agent->getPosition().y - agent->getSize().y / 2);
	rectHitbox.setPosition(hitBoxPosition);
}

void AgentInfoPanel::setAgent(Agent* agent)
{
	if (this->agent == agent)
		return;

	this->agent = agent;

	if(agent == nullptr)
		return;

	if(agent->getAgentType() == "Customer")
	{
		Customer* customer = dynamic_cast<Customer*>(agent);
		bodyParts = &customer->getBodyParts();
	}
	else
	{
		bodyParts = nullptr;
	}

	sprAgent.setTexture(agent->getTexture());
	rectHitbox.setSize(sf::Vector2f(agent->getGlobalBounds().width, agent->getGlobalBounds().height));

	txtName.setString(agent->getAgentName());
	txtPizza.setString(agent->getFavouritePizza());
	txtPizza.setCharacterSize(60);

	sf::FloatRect rectTextBounds = txtPizza.getGlobalBounds();
	sf::FloatRect rectPanelBounds = sprPanel.getGlobalBounds();

	while(rectTextBounds.width > rectPanelBounds.width)
	{
		txtPizza.setCharacterSize(txtPizza.getCharacterSize() - 1);
		rectTextBounds = txtPizza.getGlobalBounds();
	}

	//Customer *cust = dynamic_cast<Customer*>(agent);

	txtReliability.setString(std::to_string((int)agent->getReliability()) + "%");
}

Agent* AgentInfoPanel::getAgent() const
{
	return agent;
}

void AgentInfoPanel::draw(sf::RenderWindow& window)
{
	window.draw(sprPanel);

	if (agent == nullptr)
	{
		sprAgent.setColor(sf::Color::White);
		sprAgent.setTexture(txtrAgentDefault);
		window.draw(sprAgent);
		return;
	}
	else
	{
		sprAgent.setColor(sf::Color::White);
		window.draw(sprAgent);
	}

	if(bodyParts != nullptr)
	{
		for (auto const& bodyPart : *bodyParts)
		{
			sprAgent.setTexture(*bodyPart.second.getTexture());
			sprAgent.setColor(bodyPart.second.getColor());
			window.draw(sprAgent);
		}
	}

	window.draw(rectHitbox);
	
	window.draw(txtStateHeader);
	window.draw(txtState);

	window.draw(txtNameHeader);
	window.draw(txtName);

	std::string agentType = agent->getAgentType();
	if(agentType == "Customer")
	{
		window.draw(txtPizzaHeader);
		window.draw(txtPizza);
		window.draw(txtSatisfactionHeader);
		starRating.draw(window);
	}
	else if(agentType == "Waiter")
	{
		window.draw(txtReliabilityHeader);
		window.draw(txtReliability);
	}

}


void AgentInfoPanel::update()
{
	if (agent == nullptr)
	{
		sprAgent.setTexture(txtrAgentDefault);
		return;
	}

	txtState.setString(agent->getStateName());
	starRating.setRating(agent->getSatisfaction());

	repositionElements();

}

AgentInfoPanel::AgentInfoPanel()
{

	if(!txtrPanel.loadFromFile("Assets/Sidebar/Sidebar.png"))
	{
		printf("Error blah blah\n");
	}
	if(!txtrAgentDefault.loadFromFile("Assets/Agent/General/Silhouette.png"))
	{
		printf("BAD");
	}

	if(!fntDefault.loadFromFile("Assets/Fonts/Inconsolata.ttf"))
	{
		printf("sdasd\n");
	}

	sprPanel.setTexture(txtrPanel);
	sprPanel.setPosition(sf::Vector2f(928, 32));

	sprAgent.setTexture(txtrAgentDefault);
	sprAgent.setPosition(sf::Vector2f(983, 100));
	sprAgent.setScale(sf::Vector2f(3, 3));

	txtNameHeader.setFont(fntDefault);
	txtNameHeader.setFillColor(sf::Color::White);
	txtNameHeader.setCharacterSize(32);
	txtNameHeader.setStyle(sf::Text::Style::Bold);
	txtNameHeader.setString("Name");
	txtNameHeader.setScale(0.5f, 0.5f);


	txtName.setFont(fntDefault);
	txtName.setFillColor(sf::Color::White);
	txtName.setCharacterSize(32);
	txtName.setScale(0.5f, 0.5f);

	txtSatisfactionHeader.setFont(fntDefault);
	txtSatisfactionHeader.setFillColor(sf::Color::White);
	txtSatisfactionHeader.setCharacterSize(32);
	txtSatisfactionHeader.setStyle(sf::Text::Style::Bold);
	txtSatisfactionHeader.setString("Satisfaction");
	txtSatisfactionHeader.setScale(0.5f, 0.5f);

	txtStateHeader.setFont(fntDefault);
	txtStateHeader.setFillColor(sf::Color::White);
	txtStateHeader.setCharacterSize(32);
	txtStateHeader.setStyle(sf::Text::Style::Bold);
	txtStateHeader.setString("State");
	txtStateHeader.setScale(0.5f, 0.5f);

	txtState.setFont(fntDefault);
	txtState.setFillColor(sf::Color::White);
	txtState.setCharacterSize(32);
	txtState.setScale(0.5f, 0.5f);

	txtPizzaHeader.setFont(fntDefault);
	txtPizzaHeader.setFillColor(sf::Color::White);
	txtPizzaHeader.setCharacterSize(32);
	txtPizzaHeader.setStyle(sf::Text::Style::Bold);
	txtPizzaHeader.setString("Favorite Pizza");
	txtPizzaHeader.setScale(0.5f, 0.5f);

	txtPizza.setFont(fntDefault);
	txtPizza.setFillColor(sf::Color::White);
	txtPizza.setCharacterSize(32);
	txtPizza.setScale(0.5f, 0.5f);

	txtReliabilityHeader.setFont(fntDefault);
	txtReliabilityHeader.setFillColor(sf::Color::White);
	txtReliabilityHeader.setCharacterSize(32);
	txtReliabilityHeader.setStyle(sf::Text::Style::Bold);
	txtReliabilityHeader.setString("Reliability");
	txtReliabilityHeader.setScale(0.5f, 0.5f);

	txtReliability.setFont(fntDefault);
	txtReliability.setFillColor(sf::Color::White);
	txtReliability.setCharacterSize(32);
	txtReliability.setScale(0.5f, 0.5);

	rectHitbox.setFillColor(sf::Color(0, 0, 0, 25));
	rectHitbox.setOutlineColor(sf::Color::Black);
	rectHitbox.setOutlineThickness(1);

}


AgentInfoPanel::~AgentInfoPanel()
{
}
