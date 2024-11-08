#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "PhysicScene.h"
#include "GeneradorParticulas.h"
#include "GravityGenerator.h"
#include "WindGenerator.h"
#include "WhirlwindGenerator.h"
#include "ExplosionGenerator.h"
#include "HookeForce.h"
#include <iostream>

std::string display_text = "This";

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

using Generator = GeneradorParticulas<std::uniform_real_distribution<double>,
	std::uniform_real_distribution<double>,
	std::uniform_real_distribution<double>,
	std::normal_distribution<double>>;

PhysicScene* mPS;
Generator* parGen;
GravityGenerator* grav;
WindGenerator* wind;
WhirlwindGenerator* tornado;
ExplosionGenerator* explode = nullptr;
HookeForce* spring = nullptr;

// Initialize physics engine
void initPhysics(bool interactive)
{

	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	mPS = new PhysicScene(80,500);

	mPS->initScene();
	//a = new Particle(Vector3(0, 0, 0), Vector3(1,0,0),0.98);


	parGen = new Generator(4, 0.02);
	//parGen->setInitialVel(Vector3(-50, 0, -50), Vector3(50, 30, 50));
	//parGen->setInitialVel(Vector3(0, -5, 0), Vector3(0, -5,0));
	parGen->setInitalPosVar(Vector3(0,-5,0), Vector3(0,5,0));
	parGen->setInitialVel(Vector3(-30,5,-30), Vector3(30,15, 30));
	parGen->setParticlesPerSpawn(10);
	parGen->setInitialPos(Vector3(0, 10, 0));
	parGen->setParticlesAliveCond([](Particle* p) {return p->getPos().y > 0; });
	parGen->setParticleColor(Color(0, 1, 1, 1));
	parGen->setMassInverse(1);

	grav = new GravityGenerator(mPS,Vector3(0,-9.8,0));
	wind = new WindGenerator(mPS,Vector3(5, 10, 4), 1, 0,Vector3(0,50,0),Vector3(10,10,10));

	tornado = new WhirlwindGenerator(mPS, 2, 0, Vector3(0, 50, 0), Vector3(60, 60, 60), 5,2);

	parGen->addForceGen(grav);
	parGen->addForceGen(tornado);

	GeometrySpec geom;
	geom.shape = SPHERE;
	geom.sphere.radious = 1;

	Particle* mPar = new Particle(Vector3(20, 10, 0), geom, 1,0.98, Color(1, 0, 0, 1));
	
	mPar->setDeathFunc([](Particle* p) {return p->getPos().y > 0; });

	mPS->addParticle(mPar);

	spring = new HookeForce(Vector3(0, 30, 0), mPar, 4, 5);

	//grav->suscribeParticle(mPar); 
	//wind->suscribeParticle(mPar);
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	spring->update(t);
	grav->update(t);
	//wind->update(t);
	tornado->update(t,mPS->getParticleList());
	mPS->updateScene(t);
	//parGen->update(t);
	//a->integrate(t);
	gScene->simulate(t);
	gScene->fetchResults(true);


	//grav->clearParticles();
	//wind->clearParticles();
	parGen->clearParticles();
	mPS->clearParticles();
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	delete mPS;
	delete parGen;
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	mPS->keyPress(key, camera);

	switch (toupper(key))
	{
	case 'E':
		if (explode != nullptr) {
			parGen->removeForce(explode); 
			delete explode;
		}
		explode = new ExplosionGenerator(Vector3(3,10,3),100,0.5,3000);
		parGen->addForceGen(explode);
		break;
	default:
		break;
	}

	//switch(toupper(key))
	//{
	////case 'B': break;
	////case ' ':	break;
	//case ' ':
	//{
	//	break;
	//}
	//case 'I':
	//{
	//	a->accelerate(Vector3(0, 0, -1));
	//	break;
	//}
	//case 'K':
	//{
	//	a->accelerate(Vector3(0, 0, 1));
	//	break;
	//}
	//case 'J':
	//{
	//	a->accelerate(Vector3(-1, 0, 0));
	//	break;
	//}
	//case 'L':
	//{
	//	a->accelerate(Vector3(1, 0, 0));
	//	break;
	//}
	//default:
	//	break;
	//}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}