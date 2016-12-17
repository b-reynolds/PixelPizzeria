#include "Rat.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Map.h"
#include "Vector.h"
#include "Random.h"
#include "Simulation.h"
#include <math.h>
#include "DebugUtil.h"

Rat::Rat()
{
	txtrRat.loadFromFile("Assets/Rat/rat.png");
	sprRat.setTexture(txtrRat);
	sf::FloatRect rectRatBounds = sprRat.getGlobalBounds();
	sprRat.setOrigin(rectRatBounds.width / 2, rectRatBounds.height / 2);
	sprRat.setPosition(0, 0);

	sf::FloatRect spawnArea = sf::FloatRect(Map::BORDER_SIZE - sprRat.getGlobalBounds().width / 2.0f,
		Map::BORDER_SIZE - sprRat.getGlobalBounds().height / 2.0f,
			Map::SIZE_X * Map::TILE_SIZE + sprRat.getGlobalBounds().height / 2.0f,
				Map::SIZE_Y * Map::TILE_SIZE + sprRat.getGlobalBounds().height / 2.0f);

	spawnPoints.push_back(SpawnPoint(sf::Vector2f(spawnArea.left, spawnArea.top), sf::Vector2f(1, 1))); // Top Left
	spawnPoints.push_back(SpawnPoint(sf::Vector2f(spawnArea.left, spawnArea.top + spawnArea.height / 2.0f), sf::Vector2f(1, 0))); // Left
	spawnPoints.push_back(SpawnPoint(sf::Vector2f(spawnArea.left, spawnArea.left + spawnArea.height), sf::Vector2f(1, -1))); // Bottom Left
	spawnPoints.push_back(SpawnPoint(sf::Vector2f(spawnArea.left + spawnArea.width / 2.0f, spawnArea.top), sf::Vector2f(0, 1))); // Top Center
	spawnPoints.push_back(SpawnPoint(sf::Vector2f(spawnArea.left + spawnArea.width / 2.0f, spawnArea.top + spawnArea.height), sf::Vector2f(0, -1))); // Bottom Center
	spawnPoints.push_back(SpawnPoint(sf::Vector2f(spawnArea.left + spawnArea.width, spawnArea.top), sf::Vector2f(-1, 1))); // Top Right
	spawnPoints.push_back(SpawnPoint(sf::Vector2f(spawnArea.left + spawnArea.width, spawnArea.top + spawnArea.height / 2.0f), sf::Vector2f(-1, 0))); // Right
	spawnPoints.push_back(SpawnPoint(sf::Vector2f(spawnArea.left + spawnArea.width, spawnArea.top + spawnArea.height), sf::Vector2f(-1, -1))); // Bottom Right
	reset();
}

Rat::~Rat()
{
}

sf::FloatRect Rat::getGlobalBounds() const
{
	sf::FloatRect bounds = sprRat.getGlobalBounds();
	bounds.width *= 3;
	bounds.height *= 3;
	bounds.left -= bounds.width / 2;
	bounds.top -= bounds.height / 2;
	return bounds;
}

void Rat::update()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		reset();
	}

	sf::FloatRect ratBounds = sprRat.getGlobalBounds();
	sf::FloatRect winBounds = sf::FloatRect(Map::BORDER_SIZE - sprRat.getGlobalBounds().width / 2.0f,
		Map::BORDER_SIZE - sprRat.getGlobalBounds().height / 2.0f,
		Map::SIZE_X * Map::TILE_SIZE + sprRat.getGlobalBounds().height / 2.0f,
		Map::SIZE_Y * Map::TILE_SIZE + sprRat.getGlobalBounds().height / 2.0f);

	if(!ratBounds.intersects(winBounds))
	{
		reset();
	}

	wander();
	acceleration = Vector::limit(acceleration, MAX_FORCE);
	velocity += acceleration;
	Vector::limit(velocity, MAX_SPEED);
	move(velocity * Simulation::deltaTime);
	rotate(velocity);
	acceleration = sf::Vector2f(0, 0);
}

void Rat::draw(sf::RenderWindow& window) const
{
	window.draw(sprRat);
	//DebugUtil::drawLine(window, getPosition(), circleCenter, sf::Color(255, 255, 255, 75));
	//DebugUtil::drawLine(window, getPosition(), wanderTarget, sf::Color(255, 0, 0, 125));
	//DebugUtil::drawCircle(window, circleCenter, CIRCLE_RADIUS, sf::Color(0, 255, 255, 75));
}

void Rat::seek(const sf::Vector2f &target)
{
	sf::Vector2f desiredVelocity = Vector::normalize(target - getPosition()) * MAX_SPEED;
	sf::Vector2f steering = desiredVelocity - velocity;
	Vector::limit(steering, MAX_FORCE);
	addForce(steering);
}

void Rat::addForce(const sf::Vector2f& force)
{
	acceleration += force;
}

void Rat::wander()
{
	circleCenter = getPosition() + Vector::normalize(velocity) * CIRCLE_DISTANCE;
	sf::Vector2f displacement = spawnPoint.direction;
	displacement *= CIRCLE_RADIUS;
	float len = Vector::length(displacement);
	displacement.x = cos(wanderAngle) * len;
	displacement.y = sin(wanderAngle) * len;
	wanderAngle += Random::getInstance()->nextDouble() * ANGLE_CHANGE - ANGLE_CHANGE * 0.5f;
	wanderTarget = circleCenter + displacement;
	seek(wanderTarget);
}

void Rat::reset()
{
	spawnPoint = spawnPoints[Random::getInstance()->getRandomInt(0, spawnPoints.size() - 1)];
	setPosition(spawnPoint.position);
	velocity = spawnPoint.direction;
	rotate(spawnPoint.direction);
}

void Rat::move(const sf::Vector2f& distance)
{
	setPosition(getPosition() + distance);
}

void Rat::rotate(const sf::Vector2f& direction)
{
	sprRat.setRotation(atan2(direction.y, direction.x) * 180 / static_cast<float>(M_PI) + 90);
}

void Rat::setPosition(const sf::Vector2f &position)
{
	sprRat.setPosition(position);
}

sf::Vector2f Rat::getPosition() const
{
	return sprRat.getPosition();
}