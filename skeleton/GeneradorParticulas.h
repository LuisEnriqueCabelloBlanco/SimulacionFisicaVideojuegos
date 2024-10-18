#pragma once
#include <random>
#include <functional>
//#include "Particle.h"

class Particle;

class GeneradorParticulas
{
public:
	GeneradorParticulas(double low, double upper,double particleRate) :uRandGen(low, upper),particleRate(particleRate) {
		currentTime = 0;
		nextSpawnTime = particleRate;
	}

	void update(double dt);

	void addRandomProcess(std::function<void(Particle* par, std::uniform_real_distribution<double> rand)> func);

private:
	void addParticle();

	double particleRate;
	Vector3 basePosition;

	double nextSpawnTime;
	double currentTime;

	std::vector<*Particle> mParticles;
	std::default_random_engine engine;
	std::uniform_real_distribution<double> uRandGen;
};

