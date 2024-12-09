#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <list>
#include "Particle.h"
#include "ForceGenerator.h"
#include "SolidoRigido.h"
#include "DualHookForce.h"

using ObjectsList = std::list<Particle*>;
using ObjectListIt = std::list<Particle*>::iterator;

class Proyectile;

class PhysicScene
{
public:
	PhysicScene();
	PhysicScene(double simulatedSpeed, double realSpeed);
	PhysicScene(PxPhysics* px,const PxSceneDesc& desc);
	virtual ~PhysicScene();

	void keyPress(unsigned char key, const physx::PxTransform& camera);

	void initScene();

	Particle* addParticle(const Vector3& pos, const GeometrySpec& geom,double massInv=0, double damping = 0.98, const Color& color = Color(1,1,1,1));
	void addParticle(Particle* par) { particles.push_back(par); }

	const std::list<Particle*>& getParticleList() const { return particles; }
	

	Proyectile* createProyectile(double mass,const Vector3& initPos, const Vector3& initSpeed);
	Proyectile* createProyectile(double mass,const Vector3& initPos, const Vector3& initSpeed, const GeometrySpec& geom);

	void addForce(ForceGenerator* force) { forces.push_back(force); }
	void addForce(DualHookForce* force) { muelles.push_back(force); }

	void removeForce(ForceGenerator* force) { forces.remove(force); }

	void clearParticles();

	void updateScene(double dt);
private:
	/// <summary>
	/// makes the spheres representing the reference axis
	/// </summary>
	/// <param name="axisFactor">scale of the base vectors</param>
	/// <param name="sphereRadius">radius of the spheres representing the vertices of the base vectors</param>
	void makeAxis(float axisFactor, float sphereRadius);

	double gravityValue;

	double gravitySimulationFactor;
	double massSimulationFactor;
	double speedSimulatinFactor;

	//std::list<ForceGenerator*> forces;

	std::list<ForceGenerator*>forces;
	std::list<Particle*>particles;
	std::list<SolidoRigido*> solidosRigidos;
	std::list<DualHookForce*> muelles;
	std::list<ObjectListIt> toDelete;

	//reference objects
	Particle* c;
	Particle* x;
	Particle* y;
	Particle* z;

	PxPhysics* gPhysics;
	PxScene* gScene;
	SolidoRigido* sol;
};

