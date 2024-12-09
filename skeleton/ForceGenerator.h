#pragma once
#include <list>
#include<functional>
#include "Particle.h"
#include "SolidoRigido.h"

class PhysicScene;

class ForceGenerator
{
public:
	ForceGenerator(PhysicScene* pS):mPs(pS) {}
	ForceGenerator():mPs(nullptr){}

	virtual void update(double dt);

	template<class Obj=Particle>
	void update(double dt, const std::list<Obj*>& list) {
		time += dt;
		for (auto p : list) {
			if (cond(p)) {
				p->addForce(calculateForce(p));
			}
		}
	}

	template<>
	void update<SolidoRigido>(double dt, const std::list<SolidoRigido*>& list) {
		time += dt;
		for (auto p : list) {
			if (condS(p)) {
				p->addForce(calculateForce(p));
			}
		}
	}


	virtual Vector3 calculateForce(Particle* par)=0;
	virtual Vector3 calculateForce(SolidoRigido* rig)=0;

protected:
	PhysicScene* mPs;
	//function to determine if a particle needs to recive the force of the generator
	std::function<bool(Particle*)> cond = [](Particle* p) {return true; };
	std::function<bool(SolidoRigido*)> condS = [](SolidoRigido* p) {return true; };
	

	double time =0;
};

