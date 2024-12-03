#pragma once
#include "Proyectile.h"
#include "Vec3Rand.h"
#include <vector>
#include <random>
#include <functional>
#include <list>
#include "ForceGenerator.h"
#include "Particle.h"

using ObjectsList = std::list<Particle*>;
using ObjectListIt = std::list<Particle*>::iterator;


template<typename RanPos = std::uniform_real_distribution<double>,
	typename RanVel = std::uniform_real_distribution<double>,
	typename RanLive = std::uniform_real_distribution<double>,
	typename RanGen = std::uniform_real_distribution<double>>
class GeneradorParticulas
{
public:

	GeneradorParticulas(std::pair<double, double> liveTime,std::pair<double,double> randGentime = {1.0,1.0}) :
		uRandGenTime(randGentime.first,randGentime.second),uRandLiveTime(liveTime.first,liveTime.second),uRandMassInverse(-0.2,0.2) {
		currentTime = 0;
		nextSpawnTime = particleRate;
		particlesAliveCond = [](Particle* p) {return true; };

		GeometrySpec geom;
		geom.shape = SPHERE;
		geom.sphere.radious = 1;
		setShape(geom);
	}


	GeneradorParticulas(double liveTime, double randTime) :
		GeneradorParticulas({ liveTime,liveTime }, { randTime,randTime })
	{

	}
	void update(double dt)
	{
		currentTime += dt;
		if (currentTime > nextSpawnTime) {
			for (int i = 0; i < particlesPerSpawn; i++) {
				addParticle();
			}
			nextSpawnTime = particleRate + uRandGenTime(gen);
			currentTime = 0;
		}

		for (auto forceGen : forces) {
			forceGen->update(dt, mParticles);
		}

		for (ObjectListIt it = mParticles.begin(); it != mParticles.end(); ++it) {
			(*it)->update(dt);
			if (!(*it)->getAlive()) {
				toDelete.push_back(it);
			}
		}

	}

	inline void setInitalPosVar(const Vector3& a,const Vector3& b) { position.setRandom(a, b);};
	void setInitialVel(const Vector3& a,const Vector3& b) { initVel.setRandom(a, b); };
	void setParticlesPerSpawn(int pCount) { particlesPerSpawn = pCount; }
	void setParticlesAliveCond(const std::function<bool(Particle* par)>& func) { particlesAliveCond = func; }
	void setShape(const GeometrySpec& geom) { particleShape = geom; }
	void setInitialPos(const Vector3& iniPos) { basePosition = iniPos; }
	void setParticleColor(const Color& col) { pColor = col; }
	void setMassInverse(double invMass) { massInverse = invMass; }

	void addForceGen(ForceGenerator* fg) {
		forces.push_back(fg);
	}

	void removeForce(ForceGenerator* fg) {
		forces.remove(fg);
	}

	void clearParticles()
	{
		while (!toDelete.empty()) {
			delete (*toDelete.front());
			mParticles.erase(toDelete.front());
			toDelete.pop_front();
		}
	}

	~GeneradorParticulas() {
		for (auto p : mParticles) {
			delete p;
		}
	}

protected:
	void addParticle()
	{
		Particle* pr = new Particle(basePosition + position(), particleShape, massInverse /*+ uRandMassInverse(gen)*/, 0.8, pColor, uRandLiveTime(gen));
		//pr->accelerate(Vector3(0, -9.8, 0));
		pr->setDeathFunc(particlesAliveCond);
		pr->setVel(initVel());

		mParticles.push_back(pr);
	}

	GeometrySpec particleShape;

	Color pColor = Color(1,2,1,1);

	int particlesPerSpawn = 1;
	Vector3 basePosition = Vector3(0);
	double particleRate = 0;
	Vector3 gravityAcc = Vector3(0, -9.8, 0);


	double nextSpawnTime;
	double currentTime;

	double massInverse=0;

	std::function<bool(Particle*)> particlesAliveCond;

	std::default_random_engine gen;
	std::uniform_real_distribution<double> uRandGenTime;
	std::uniform_real_distribution<double> uRandLiveTime;
	std::uniform_real_distribution<double> uRandMassInverse;
	Vector3Rand<RanPos> position;
	Vector3Rand<RanVel> initVel;

	ObjectsList mParticles;
	std::list<ObjectListIt> toDelete;
	std::list<ForceGenerator*> forces;
};

