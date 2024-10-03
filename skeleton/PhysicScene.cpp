#include "PhysicScene.h"
#include "Particle.h"

PhysicScene::PhysicScene()
{

}
PhysicScene::~PhysicScene()
{
}
void PhysicScene::keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	Particle* a = particles[0];
	switch (toupper(key))
	{
		//case 'B': break;
		//case ' ':	break;
	case ' ':
	{
		break;
	}
	case 'I':
	{
		a->accelerate(Vector3(0, 0, -1));
		break;
	}
	case 'K':
	{
		a->accelerate(Vector3(0, 0, 1));
		break;
	}
	case 'J':
	{
		a->accelerate(Vector3(-1, 0, 0));
		break;
	}
	case 'L':
	{
		a->accelerate(Vector3(1, 0, 0));
		break;
	}
	default:
		break;
	}

}
void PhysicScene::initScene()
{
	Particle::GeometrySpec geom;
	geom.shape = Particle::SPHERE;
	geom.sphere.radious = 1;
	addParticle(new Particle(Vector3(0, 0, 0),geom));
}
void PhysicScene::addParticle(Particle* par)
{
	particles.push_back(par);
}

void PhysicScene::createProyectile(Vector3 initPos, Vector3 initForce)
{
	Particle::GeometrySpec geom;
	geom.shape = Particle::SPHERE;
	geom.sphere.radious = 1;
	addParticle(new Particle(Vector3(0, 0, 0), geom));
}





void PhysicScene::updateScene(double dt)
{
	for (auto p : particles) {
		p->integrate(dt);
	}
}
