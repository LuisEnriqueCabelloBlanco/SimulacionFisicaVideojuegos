#include "PhysicScene.h"
#include "Particle.h"
#include "Proyectile.h"
#include <iostream>
PhysicScene::PhysicScene()
{

}
PhysicScene::~PhysicScene()
{
	delete c;
	delete x;
	delete y;
	delete z;

	for (auto p : particles) {
		delete p;
	}
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


	case '1': 
	{
		Proyectile * pr = createProyectile(300, Vector3(0, 0, 0), Vector3(1, 1, 0).getNormalized()*250);
		pr->accelerate(Vector3(0, gravityValue, 0));
		break;
	}
	case '2':
	{
		Proyectile* pr = createProyectile(300, Vector3(0, 0, 0), Vector3(1, 1, 0).getNormalized() * 1800);
		pr->accelerate(Vector3(0, gravityValue, 0));
		break;
	}
	case '3':
	{
		Proyectile* pr = createProyectile(300, Vector3(0, 0, 0), Vector3(1, 1, 0).getNormalized() * 300000000);
		pr->accelerate(Vector3(0, gravityValue, 0));
		break;
	}
	default:
		break;
	}

}
void PhysicScene::initScene()
{
	makeAxis(20,0.5);

	Particle::GeometrySpec geom;
	geom.shape = Particle::CUBE;
	geom.box.x=2;
	geom.box.y=2;
	geom.box.z=2;
	addParticle(new Particle(Vector3(0, 0, 0),geom));
	//Proyectile* pr =createProyectile(1, Vector3(0, 0, 0), Vector3(7, 10, 0));
	//pr->addForce(Vector3(0, -9.8, 0));
}
void PhysicScene::addParticle(Particle* par)
{
	particles.push_back(par);
}

Proyectile* PhysicScene::createProyectile(double mass,const Vector3& initPos,const Vector3& initSpeed)
{
	Particle::GeometrySpec geom;
	geom.shape = Particle::SPHERE;
	geom.sphere.radious = 1;
	Proyectile* proj= new Proyectile(mass,initPos,geom,initSpeed);
	addParticle(proj);
	return proj;
}

void PhysicScene::clearParticles()
{
	while (!toDelete.empty()) {
		
		delete (*toDelete.front());
		particles.erase(toDelete.front());
		toDelete.pop_front();
		
	}
}

void PhysicScene::makeAxis(float axisFactor,float sphereRadius)
{
	c = new Particle(Vector3(0, 0, 0), Vector3(0), 0.5); c->setColor(Vector4(1.0));
	x = new Particle(Vector3(axisFactor, 0, 0), Vector3(0), 0.5); x->setColor(Vector4(1, 0, 0, 1));
	y = new Particle(Vector3(0, axisFactor, 0), Vector3(0), 0.5); y->setColor(Vector4(0, 1, 0, 1));
	z = new Particle(Vector3(0, 0, axisFactor), Vector3(0), 0.5); z->setColor(Vector4(0, 0, 1, 1));
}





void PhysicScene::updateScene(double dt)
{
	for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end();++it) {
		(*it)->integrate(dt);
		if ((*it)->getPos().y < -2) {
			toDelete.push_back(it);
		}
	}
}
