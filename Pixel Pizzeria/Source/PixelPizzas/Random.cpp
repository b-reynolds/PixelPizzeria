#include "Random.h"
#include <random>
#include <ctime>

Random* Random::instance = nullptr;

unsigned int Random::getRandomInt(const unsigned int& min, const unsigned int& max)
{
	std::uniform_int_distribution<unsigned int> uniformDistribution(min, max);
	return uniformDistribution(randomDevice);
}

unsigned Random::getRandomInt(const std::pair<int, int>& range)
{
	std::uniform_int_distribution<unsigned int> uniformDistribution(range.first, range.second);
	return uniformDistribution(randomDevice);
}

float Random::nextDouble()
{
	static std::mt19937 rng_engine((unsigned)time(nullptr));
	static std::uniform_real_distribution<float> distribution;
	return distribution(rng_engine);
}

Random::Random()
{
	std::default_random_engine generator(randomDevice());
}

Random* Random::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Random();
	}
	return instance;
}

Random::~Random()
{
	delete instance;
}
