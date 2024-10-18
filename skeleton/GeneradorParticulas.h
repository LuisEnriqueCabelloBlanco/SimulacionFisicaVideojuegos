#pragma once
#include "Particle.h"
#include <vector>
#include <random>
#include <functional>
#include <list>

class U_Vector3Rand {
public:
	U_Vector3Rand():rX(0,0), rY(0,0), rZ(0,0) {

	}
	U_Vector3Rand(Vector3 a, Vector3 b):rX(a.x,b.x), rY(a.y, b.y),rZ(a.z,b.z) {
		
	}
	
	void setRandom(Vector3 a, Vector3 b) {
		rX = std::uniform_real_distribution<double>(a.x, b.x);
		rY = std::uniform_real_distribution<double>(a.y, b.y);
		rZ = std::uniform_real_distribution<double>(a.z, b.z);
	}

	Vector3 operator()() {
		return Vector3(rX(gen), rY(gen), rZ(gen));
	}
private:
	std::default_random_engine gen;

	std::uniform_real_distribution<double> rX;
	std::uniform_real_distribution<double> rY;
	std::uniform_real_distribution<double> rZ;
};

class PhysicScene;

class GeneradorParticulas
{
public:
	GeneradorParticulas(){
		currentTime = 0;
		nextSpawnTime = particleRate;
	}

	void update(double dt);

	void clearParticles();

private:
	void addParticle();

	double particleRate;
	Vector3 basePosition;

	double nextSpawnTime;
	double currentTime;

	PhysicScene* mPS;

	std::vector<Particle*> mParticles;


	std::default_random_engine gen;

	std::uniform_real_distribution<double> uRandGenTime;
	U_Vector3Rand position;
	U_Vector3Rand initVel;

};

