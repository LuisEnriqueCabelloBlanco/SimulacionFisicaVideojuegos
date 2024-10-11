#pragma once
#include "Particle.h"
#include <random>
class GeneradorGausiano
{
public:
	GeneradorGausiano(double mean, double std);


	//std::uniform_real_distribution<double>uni;
	std::normal_distribution<double>normal;
};

