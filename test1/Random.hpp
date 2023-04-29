#pragma once

#include <random>

class Random
{
public:
	Random() :
		engine(randomDev()), dist(0.0f, 1.0f)
	{

	}

	float RandomFloat()
	{
		return dist(engine);
	}

private:
	std::random_device randomDev;
	std::mt19937 engine;
	std::uniform_real_distribution<float> dist;
};