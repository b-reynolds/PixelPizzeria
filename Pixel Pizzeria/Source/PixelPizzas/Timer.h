#pragma once
#include <SFML/System/Clock.hpp>

class Timer
{

private:

	sf::Clock clock;
	sf::Int32 time;
	sf::Int32 interval;

public:

	bool hasElapsed() const;

	void setInterval(const sf::Int32 &interval);
	void reset();

	Timer();
	Timer(const sf::Int32 &interval);
	~Timer();

};

