#include "PhysicScene.h"
#include "Particle.h"
#include "Proyectile.h"
#include "core.hpp"
#include <iostream>
#include "SolidoRigido.h"
#include "GravityGenerator.h"
#include "WindGenerator.h"
#include "GeneradorSolidoRigido.h"
#include "HookeForce.h"
#include "SpiderWeb.h"
#include "SpiderSling.h"
#include <string>

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
	//desc.simulationEventCallback = this;
	gPhysics = px;
	gScene = px->createScene(desc);
	floorMaterial = gPhysics->createMaterial(1, 1, 0);
	gScene->setSimulationEventCallback(this);
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
	//Particle* a = (*particles.begin());
	switch (toupper(key))
	{
		//case 'B': break;
		//case ' ':	break;
	case ' ':
	{
		if (hook != nullptr) delete hook;
		hook = nullptr;
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
	case 'Q': {

		new SpiderWeb(camera.p, GetCamera()->getDir() * 50, this,gScene);

		break;
	}
	case 'W': {
		Vector3 aux = Vector3(GetCamera()->getDir().x, sol->getVelocity().y, GetCamera()->getDir().z).getNormalized() * 10;

		//sol->addForce(aux);
		sol->setVelocity(aux);
		break;
	}
	case 'S':{
		Vector3 aux = Vector3(GetCamera()->getDir().x, -sol->getVelocity().y, GetCamera()->getDir().z).getNormalized() * 10;

		//sol->addForce(aux);
		sol->setVelocity(-aux);
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
	geom.shape = SPHERE;
	geom.box.x=2;
	geom.box.y=2;
	geom.box.z=2;
	geom.sphere.radious = 1.5;

	
	//Suelo
	PxTransform pose(Vector3(0, 0, 0));
	PxRigidStatic* statico = gPhysics->createRigidStatic(pose);
	PxShape* s = CreateShape(PxBoxGeometry(100,0.01,100),floorMaterial);
	//s->setMaterials();
	statico->attachShape(*s);
	RenderItem* obj = new RenderItem(s, statico, Color(1, 1, 1, 0.5));
	gScene->addActor(*statico);


	//edifisi
	PxTransform pose1(Vector3(0, 10, 20));
	PxRigidStatic* statico1 = gPhysics->createRigidStatic(pose1);
	PxShape* s1 = CreateShape(PxBoxGeometry(20, 10, 5), floorMaterial);
	statico1->attachShape(*s1);
	RenderItem* obj1 = new RenderItem(s1, statico1, Color(1, 1, 0, 1));
	gScene->addActor(*statico1);



	//edifisi
	PxTransform pose2(Vector3(0, 10, -20));
	PxRigidStatic* statico2 = gPhysics->createRigidStatic(pose2);
	PxShape* s2 = CreateShape(PxBoxGeometry(20, 10, 5), floorMaterial);
	statico2->attachShape(*s2);
	RenderItem* obj2 = new RenderItem(s2, statico2, Color(1, 1, 0, 1));
	gScene->addActor(*statico2);

	//Main Character
	solidosRigidos.push_back((sol = new SolidoRigido(Vector3(10, 10, 0), geom, gPhysics, gScene,0,Color(1,1,1,0))));
	sol->unrender();
	sol->getRigid()->setName("Manuel");
	sol->getRigid()->setMassSpaceInertiaTensor(Vector3(0, 0, 0));
	sol->getRigid()->setMass(70);
	//Build rain

	generators.push_back(new GeneradorSolidoRigido<>(gScene, { 5,10 },{0.01,0.3}));
	GeometrySpec parGeom;
	parGeom.shape = SPHERE;
	parGeom.sphere.radious = 0.05;

	generators.front()->setShape(parGeom);
	generators.front()->setParticleColor(Color(0,0,0.5,0.1));
	generators.front()->setParticlesPerSpawn(100);
	generators.front()->setMassInverse(0.02);
	generators.front()->setInitialPos(Vector3(10, 30, 0));
	generators.front()->setInitalPosVar(Vector3(-10, -5, -10), Vector3(10, 0, 10));
	generators.front()->setParticlesAliveCond([](SolidoRigido* rb) {return rb->getPose().y > -1; });
	generators.front()->setInitialVel(Vector3(0, 10, 0), Vector3(0, 20, 0));
	generators.front()->addForceGen(new WindGenerator(this, Vector3(5, 0, 0), 0.03, 0, Vector3(0, 0, 0), Vector3(1000)));

	addForce(new GravityGenerator(this));
	WindGenerator* wind;
	addForce(new WindGenerator(this, Vector3(0), 0.03, 0, Vector3(0, 500, 0), Vector3(1000)));
	addForce(new WindGenerator(this, Vector3(10,0,0), 0.03, 0, Vector3(0, 0, 0), Vector3(1000)));
	//addForce(new HookeForce(Vector3(20,20,10),sol,4,5));

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

void PhysicScene::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)
{
}

void PhysicScene::onWake(PxActor** actors, PxU32 count)
{
}

void PhysicScene::onSleep(PxActor** actors, PxU32 count)
{
}

void PhysicScene::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	if (pairs[0].events.isSet(physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)) {
		for (auto par : solidosRigidos) {
			if (pairHeader.actors[0] == par->getRigid()) {
				par->onCollision(pairHeader.actors[1]);
			}
			else if (pairHeader.actors[1] == par->getRigid()) {
				par->onCollision(pairHeader.actors[0]);
			}

			//if (strcmp("Bala", pairHeader.actors[1]->getName())) {
			//	if (hook != nullptr) delete hook;
			//	hook = new HookeForce(pairHeader.actors[1]->getGlobalPose().p, sol, 5, 5);

			//}
		}
	}
}

void PhysicScene::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
}

void PhysicScene::onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
{
}


void PhysicScene::updateScene(double dt)
{
	for (auto s : muelles) {
		s->update(dt);
	}
	
	if (hook != nullptr) {
		hook->update(dt);
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
	GetCamera()->setEye(sol->getPose()+Vector3(0,3,0));

	for (auto gen : generators) {
		gen->clearParticles();
	}
}

void PhysicScene::createWeb(Vector3 position)
{
	if (hook != nullptr) {
		delete hook;
	}

	hook = new SpiderSling(position,exp(-(position - sol->getPose()).magnitude()), sol);
}
