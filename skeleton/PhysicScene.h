#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <list>
class Particle;
class Proyectile;

class PhysicScene
{
public:
	PhysicScene();
	~PhysicScene();

	void keyPress(unsigned char key, const physx::PxTransform& camera);

	void initScene();

	void addParticle(Particle* par);

	Proyectile* createProyectile(double mass,const Vector3& initPos, const Vector3& initSpeed);

	void clearParticles();

	void updateScene(double dt);
private:
	/// <summary>
	/// makes the spheres representing the reference axis
	/// </summary>
	/// <param name="axisFactor">scale of the base vectors</param>
	/// <param name="sphereRadius">radius of the spheres representing the vertices of the base vectors</param>
	void makeAxis(float axisFactor, float sphereRadius);

	double gravityValue = -100;

	std::vector<Particle*>particles;

	std::list<std::vector<Particle*>::iterator> toDelete;

	//reference objects
	Particle* c;
	Particle* x;
	Particle* y;
	Particle* z;
};

