#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
class Particle;

class PhysicScene
{
public:
	PhysicScene();
	~PhysicScene();

	void keyPress(unsigned char key, const physx::PxTransform& camera);

	void initScene();

	void addParticle(Particle* par);

	void updateScene(double dt);
private:
	std::vector<Particle*>particles;
};

