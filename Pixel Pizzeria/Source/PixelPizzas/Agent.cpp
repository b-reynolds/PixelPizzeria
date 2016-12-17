#include "Agent.h"
#include <math.h>
#include "Map.h"
#include "Simulation.h"
#include "Vector.h"
#include "Random.h"
#include "Name.h"
#include "Colours.h"

void Agent::draw(sf::RenderWindow &window)
{
	if (active)
	{
		window.draw(sprAgent);
	}
}

void Agent::setPosition(const sf::Vector2f& position)
{
	sprAgent.setPosition(position);
}

sf::Vector2f Agent::getPosition() const
{
	return sprAgent.getPosition();
}

sf::Vector2i Agent::getTilePosition() const
{
	return Map::worldToTile(sprAgent.getPosition());
}

void Agent::setPath(std::stack<sf::Vector2i> &path)
{
	while(!this->path.empty())
	{
		this->path.pop();
	}
	while(!path.empty())
	{
		sf::Vector2f destination = Map::tileToWorld(path.top());
		path.pop();
		this->path.push(destination);
	}
}

std::queue<sf::Vector2f>const & Agent::getPath() const
{
	return path;
}

void Agent::rotate(const sf::Vector2f& direction)
{
	float desiredRotation = atan2(direction.y, direction.x) * 180 / (float)M_PI - 90;
	sprAgent.setRotation(desiredRotation);
}

void Agent::move(const sf::Vector2f& velocity)
{
	sprAgent.move(velocity);
}

float Agent::getSpeed() const
{
	return speed;
}

void Agent::setActive(const bool& state)
{
	active = state;
}

void Agent::faceTile(Agent& agent, Map& map, const unsigned& tile)
{
	sf::Vector2i agentPosition = agent.getTilePosition();

	sf::Vector2i north(agentPosition.x, agentPosition.y - 1);
	sf::Vector2i east(agentPosition.x + 1, agentPosition.y);
	sf::Vector2i south(agentPosition.x, agentPosition.y + 1);
	sf::Vector2i west(agentPosition.x - 1, agentPosition.y);


	if(map.isWithinBounds(north) && map.getID(north) == tile)
	{
		agent.rotate(sf::Vector2f(0, -1));
	}
	if (map.isWithinBounds(east) && map.getID(east) == tile)
	{
		agent.rotate(sf::Vector2f(1, 0));
	}
	if (map.isWithinBounds(south) && map.getID(south) == tile)
	{
		agent.rotate(sf::Vector2f(0, 1));
	}
	if (map.isWithinBounds(west) && map.getID(west) == tile)
	{
		agent.rotate(sf::Vector2f(-1, 0));
	}

}

sf::Vector2i Agent::getNeighbourTile(Agent& agent, Map& map, const unsigned& tile)
{
	sf::Vector2i agentPosition = agent.getTilePosition();

	sf::Vector2i north(agentPosition.x, agentPosition.y - 1);
	sf::Vector2i east(agentPosition.x + 1, agentPosition.y);
	sf::Vector2i south(agentPosition.x, agentPosition.y + 1);
	sf::Vector2i west(agentPosition.x - 1, agentPosition.y);

	if(map.isWithinBounds(north) && map.getID(north) == tile)
	{
		return north;
	}
	if(map.isWithinBounds(east) && map.getID(east) == tile)
	{
		return east;
	}
	if(map.isWithinBounds(south) && map.getID(south) == tile)
	{
		return south;
	}
	if(map.isWithinBounds(west) && map.getID(west) == tile)
	{
		return west;
	}

	return sf::Vector2i(-1, -1);
}

sf::Vector2f Agent::getSize() const
{
	return sf::Vector2f(Map::TILE_SIZE, Map::TILE_SIZE);
}

bool Agent::isActive() const
{
	return active;
}

void Agent::setStateName(const std::string& stateName)
{
	this->stateName = stateName;
}

std::string Agent::getStateName() const
{
	return stateName;
}

void Agent::setSpeed(const float& speed)
{
	this->speed = speed;
}

void Agent::setAgentName(const std::string& agentName)
{
	this->agentName = agentName;
}

void Agent::followPath(Map &map)
{
	if(path.empty())
	{
		return;
	}

	sf::Vector2f position = getPosition();
	sf::Vector2f destination = path.front();
	sf::Vector2f direction = Vector::normalize(destination - position);


	sf::Vector2f nextPosition = position + (direction * speed * Simulation::deltaTime);

	if(direction == sf::Vector2f(1, 0))
	{
		if(nextPosition.x > destination.x)
		{
			nextPosition = destination;
		}
	}
	else if(direction == sf::Vector2f(-1, 0))
	{
		if(nextPosition.x < destination.x)
		{
			nextPosition = destination;
		}
	}
	else if(direction == sf::Vector2f(0, 1))
	{
		if(nextPosition.y > destination.y)
		{
			nextPosition = destination;
		}
	}
	else if(direction == sf::Vector2f(0, -1))
	{
		if(nextPosition.y < destination.y)
		{
			nextPosition = destination;
		}
	}

	setPosition(nextPosition);

	if (!hasRotated)
	{
		rotate(direction);
	}

	if (Vector::distance(getPosition(), destination) < 0.1f)
	{
		hasRotated = false;
		path.pop();
	}

}

std::string Agent::getInfo() const
{
	return "[ " + agentName + ": " + std::to_string(id) + " ] ";
}

sf::FloatRect Agent::getGlobalBounds() const
{
	return sprAgent.getGlobalBounds();
}

sf::Texture& Agent::getTexture()
{
	return txtrAgent;
}

Agent::Agent()
{
	Random* random = Random::getInstance();
	Name* names = Name::getInstance();

	speed = random->getRandomInt(200, 300);
	agentName = names->getName(gender);
	favouritePizza = names->getInstance()->getPizza();
	gender = Random::getInstance()->getRandomInt(0, 1);

	sprAgent.setOrigin(Map::TILE_SIZE / 2, Map::TILE_SIZE / 2);
}

std::string Agent::getAgentName() const
{
	return agentName;
}

void Agent::setFavouritePizza(const std::string& favouritePizza)
{
	this->favouritePizza = favouritePizza;
}

std::string Agent::getFavouritePizza() const
{
	return favouritePizza;
}

std::string Agent::getAgentType() const
{
	return agentType;
}

void Agent::setSatisfaction(const int& satisfaction)
{
	this->satisfaction = satisfaction;
}

int Agent::getSatisfaction() const
{
	return satisfaction;
}

void Agent::setReliability(const float& reliability)
{
	this->reliability = reliability;
}

float Agent::getReliability() const
{
	return reliability;
}

bool Agent::intersects(const sf::FloatRect& rect) const
{
	sf::FloatRect rectAgent = getGlobalBounds();
	return(rectAgent.left < rect.left + rect.width && rectAgent.left + rectAgent.width > rect.left &&
		rectAgent.top < rect.top + rect.height && rectAgent.top + rectAgent.height > rect.top);
}

Agent::~Agent()
{

}
