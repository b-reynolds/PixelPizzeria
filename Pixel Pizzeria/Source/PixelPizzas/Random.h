#pragma once
#include <random>

class Random
{

private:

	std::random_device randomDevice;

	static Random* instance;

	Random();

public:

	static Random* getInstance();

	unsigned int getRandomInt(const unsigned int &min, const unsigned int &max);
	unsigned int getRandomInt(const std::pair<int, int>& range);
	float nextDouble();

	~Random();


};

