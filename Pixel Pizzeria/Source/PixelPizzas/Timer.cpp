#include "Timer.h"

bool Timer::hasElapsed() const
{
	return clock.getElapsedTime().asMilliseconds() - time >= interval;
}

void Timer::setInterval(const sf::Int32 &interval)
{
	this->interval = interval;
}

void Timer::reset()
{
	time = clock.getElapsedTime().asMilliseconds();
}

Timer::Timer()
{
	interval = 0;
	time = 0;
}

Timer::Timer(const sf::Int32 &interval)
{
	this->interval = interval;
	time = 0;
}

Timer::~Timer()
{
}
