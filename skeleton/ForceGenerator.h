#pragma once
#include <list>
#include<functional>
#include "Particle.h"

class PhysicScene;

class ForceGenerator
{
public:
	ForceGenerator(PhysicScene* pS):mPs(pS) {}
	ForceGenerator():mPs(nullptr){}

	virtual void update(double dt);
	virtual void update(double dt, const std::list<Particle*>& list);

	virtual Vector3 calculateForce(Particle* par)=0;

protected:
	PhysicScene* mPs;
	//function to determine if a particle needs to recive the force of the generator
	std::function<bool(Particle*)> cond = [](Particle* p) {return true; };

	double time =0;
};

