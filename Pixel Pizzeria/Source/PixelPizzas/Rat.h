#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

struct SpawnPoint
{
	sf::Vector2f position;
	sf::Vector2f direction;

	SpawnPoint(const sf::Vector2f &position, const sf::Vector2f &direction)
	{
		this->position = position;
		this->direction = direction;
	}

	SpawnPoint()
	{
		position = sf::Vector2f(0, 0);
		direction = sf::Vector2f(0, 0);
	}
};

namespace sf {
	class RenderWindow;
}

class Rat
{

public:

	Rat();
	~Rat();

	sf::FloatRect getGlobalBounds() const;

	void update();
	void draw(sf::RenderWindow &window) const;

private:

	std::vector<SpawnPoint> spawnPoints;
	SpawnPoint spawnPoint;

	sf::Texture txtrRat;
	sf::Sprite sprRat;

	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	sf::Vector2f wanderTarget;
	float wanderAngle;

	sf::Vector2f circleCenter;

	const float CIRCLE_DISTANCE = 200.0f;
	const float CIRCLE_RADIUS = 100.0f;
	const float MAX_SPEED = 150.0f;
	const float MAX_FORCE = 0.5f;
	const float ANGLE_CHANGE = 0.087f;

	void setPosition(const sf::Vector2f &position);
	void seek(const sf::Vector2f &target);
	void addForce(const sf::Vector2f &force);
	void wander();
	void reset();
	void move(const sf::Vector2f &distance);
	void rotate(const sf::Vector2f &direction);
	
	sf::Vector2f getPosition() const;

};

