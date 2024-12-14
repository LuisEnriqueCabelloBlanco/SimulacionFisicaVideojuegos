#include "PhysicScene.h"
#include "Particle.h"
#include "Proyectile.h"
#include "core.hpp"
#include <iostream>
#include "SolidoRigido.h"
#include "GravityGenerator.h"
#include "WindGenerator.h"
#include "GeneradorSolidoRigido.h"
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

	gScene->release();
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
	geom.box.x=2;
	geom.box.y=2;
	geom.box.z=2;

	

	PxTransform pose(Vector3(0, 0, 0));
	PxRigidStatic* statico = gPhysics->createRigidStatic(pose);
	PxShape* s = CreateShape(PxBoxGeometry(100,0.01,100));
	statico->attachShape(*s);
	RenderItem* obj = new RenderItem(s, statico, Color(1, 1, 1, 0.5));
	gScene->addActor(*statico);

	/*PxTransform pose1(Vector3(0, 5, 0));
	PxRigidDynamic* din = gPhysics->createRigidDynamic(pose1);
	PxShape* s1 = CreateShape(PxBoxGeometry(1,1,1));
	din->attachShape(*s1);
	new RenderItem(s1, din, Color(0.5, 0.5, 1, 1));
	gScene->addActor(*din);

	din->addForce(Vector3(10, 10, 0));*/

	solidosRigidos.push_back((sol = new SolidoRigido(Vector3(0, 20, 0), geom, gPhysics, gScene,5,Color(1,1,1,1))));


	generators.push_back(new GeneradorSolidoRigido<>(gScene, { 0.5,1 }));

	generators.front()->setInitialPos(Vector3(10, 20, 0));
	generators.front()->setInitalPosVar(Vector3(-10, 0, 0), Vector3(10, 0, 5));
	//Particle* par =addParticle(Vector3(0, 0, 0),geom,0,0.98,Color(0,0,0,0));
	//par->setColor(Vector4(1, 1,1, 0));

	//Proyectile* pr =createProyectile(1, Vector3(0, 0, 0), Vector3(7, 10, 0));
	//pr->addForce(Vector3(0, -9.8, 0));
	addForce(new GravityGenerator(this));
	addForce(new WindGenerator(this, Vector3(0), 0.03, 0, Vector3(0, 500, 0), Vector3(1000)));
	addForce(new WindGenerator(this, Vector3(10,0,0), 1, 0, Vector3(0, 0, 0), Vector3(1000)));
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
	for (auto s : muelles) {
		s->update(dt);
	}

	for (auto f : forces) {
		f->update(dt, particles);
		f->update<SolidoRigido>(dt, solidosRigidos);
	}

	for (std::list<Particle*>::iterator it = particles.begin(); it != particles.end();++it) {
		(*it)->update(dt);
		if (!(*it)->getAlive()) {
			toDelete.push_back(it);
		}
	}

	for (auto it = solidosRigidos.begin(); it != solidosRigidos.end();) {
		(*it)->update(dt);
		if (!(*it)->getAlive()) {
			delete (*it);
			it = solidosRigidos.erase(it);
		}
		else { ++it; }
	}

	for (auto gen : generators) {
		gen->update(dt);
	}


	gScene->simulate(dt);
	gScene->fetchResults(true);
	//first person camera
	//GetCamera()->setEye(sol->getPose()+Vector3(0,0,0));
}
