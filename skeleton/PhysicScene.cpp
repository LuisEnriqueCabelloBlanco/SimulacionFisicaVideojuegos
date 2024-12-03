#include "PhysicScene.h"
#include "Particle.h"
#include "Proyectile.h"
#include "core.hpp"
#include <iostream>
PhysicScene::PhysicScene()
{

}
PhysicScene::PhysicScene(double simulatedSpeed, double realSpeed):gravityValue(-9.8)
{
	speedSimulatinFactor = simulatedSpeed/realSpeed;
	gravitySimulationFactor = pow(speedSimulatinFactor,2);
	massSimulationFactor = pow((realSpeed / simulatedSpeed),2);

	gravityValue *= gravitySimulationFactor;
}
PhysicScene::PhysicScene(PxPhysics* px,const PxSceneDesc& desc)
{
	gPhysics = px;
	gScene = px->createScene(desc);
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

	for (auto f : forces) {
		delete f;
	}
}
void PhysicScene::keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	Particle* a = (*particles.begin());
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
		Proyectile * pr = createProyectile(0.005, Vector3(0, 0, 0), Vector3(2, 1, 0).getNormalized()*30);
		pr->accelerate(Vector3(0, gravityValue*4, 0));
		pr->setDeathFunc([](Particle* pr) {return pr->getPos().y > -1; });
		break;
	}
	case '2':
	{
		Proyectile* pr = createProyectile(0.4, Vector3(0, 0, 0), Vector3(2, 1, 0).getNormalized() * 1800);
		pr->accelerate(Vector3(0, gravityValue, 0));
		break;
	}
	case '3':
	{
		Proyectile* pr = createProyectile(300, Vector3(0, 0, 0), Vector3(2, 1, 0).getNormalized() * 15000000);
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

	GeometrySpec geom;
	geom.shape = CUBE;
	geom.box.x=200;
	geom.box.y=0.5;
	geom.box.z=200;

	PxTransform pose(Vector3(0, 5, 0));
	PxRigidStatic* statico = gPhysics->createRigidStatic(pose);

	PxShape* s = CreateShape(PxSphereGeometry(1));
	statico->attachShape(*s);

	RenderItem* obj = new RenderItem(s, statico, Color(1, 1, 1, 1));

	gScene->addActor(*statico);

	//Particle* par =addParticle(Vector3(0, 0, 0),geom,0,0.98,Color(0,0,0,0));
	//par->setColor(Vector4(1, 1,1, 0));

	//Proyectile* pr =createProyectile(1, Vector3(0, 0, 0), Vector3(7, 10, 0));
	//pr->addForce(Vector3(0, -9.8, 0));
}

Particle* PhysicScene::addParticle(const Vector3& pos,const GeometrySpec& geom,double massInv,double damping,const Color& color)
{
	Particle* aux = new Particle(pos, geom,massInv, damping, color);
	particles.push_back(aux);
	return aux;
}

Proyectile* PhysicScene::createProyectile(double mass,const Vector3& initPos,const Vector3& initSpeed)
{
	GeometrySpec geom;
	geom.shape = SPHERE;
	geom.sphere.radious = 1;
	Proyectile* proj= createProyectile(mass,initPos,initSpeed,geom);
	return proj;
}

Proyectile* PhysicScene::createProyectile(double mass, const Vector3& initPos, const Vector3& initSpeed, const GeometrySpec& geom)
{
	Proyectile* proj = new Proyectile(1 / (mass * massSimulationFactor), initPos, geom, initSpeed * speedSimulatinFactor,1);
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
	for (auto f : forces) {
		f->update(dt, particles);
	}

	for (std::list<Particle*>::iterator it = particles.begin(); it != particles.end();++it) {
		(*it)->update(dt);
		if (!(*it)->getAlive()) {
			toDelete.push_back(it);
		}
	}
	gScene->simulate(dt);
	gScene->fetchResults(true);
}
