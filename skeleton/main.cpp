#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "PhysicScene.h"
#include "GeneradorParticulas.h"
#include "GravityGenerator.h"
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


	parGen = new Generator(0, 0.3);
	//parGen->setInitialVel(Vector3(-50, 0, -50), Vector3(50, 30, 50));
	//parGen->setInitialVel(Vector3(0, -5, 0), Vector3(0, -5,0));
	parGen->setInitalPosVar(Vector3(0,-5,0), Vector3(0,5,0));
	parGen->setInitialVel(Vector3(-10,5,-10), Vector3(10,15, 10));
	parGen->setParticlesPerSpawn(10);
	parGen->setInitialPos(Vector3(0, 10, 0));
	parGen->setParticlesAliveCond([](Particle* p) {return p->getPos().y > 0; });

	grav = new GravityGenerator(Vector3(0,-5,0));

	GeometrySpec geom;
	geom.shape = SPHERE;
	geom.sphere.radious = 1;

	Particle* mPar = new Particle(Vector3(0, 30, 0), geom, 30);
	
	mPar->setDeathFunc([](Particle* p) {return p->getPos().y > 0; });

	mPS->addParticle(mPar);

	grav->suscribeParticle(mPar);
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	grav->update(t);
	mPS->updateScene(t);
	//parGen->update(t);
	//a->integrate(t);
	gScene->simulate(t);
	gScene->fetchResults(true);


	grav->clearParticles();
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