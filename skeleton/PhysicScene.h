#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
class Particle;

class PhysicScene
{
public:
	PhysicScene();
	~PhysicScene();

	void keyPress(unsigned char key, const physx::PxTransform& camera);

	void initScene();

	void addParticle(Particle* par);

	void createProyectile(Vector3 initPos, Vector3 initForce);

	void updateScene(double dt);
private:
	std::vector<Particle*>particles;
};

