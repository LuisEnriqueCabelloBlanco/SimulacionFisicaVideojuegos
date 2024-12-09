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
#include "DualHookForce.h"
#include "RubberBand.h"
#include "FloatForce.h"
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
PxCooking* cooking;


using Generator = GeneradorParticulas<std::uniform_real_distribution<double>,
	std::uniform_real_distribution<double>,
	std::uniform_real_distribution<double>,
	std::normal_distribution<double>>;

PhysicScene* mPS;
Generator* parGen;

GravityGenerator* grav;
WindGenerator* wind;
WindGenerator* resistance;
WhirlwindGenerator* tornado;
ExplosionGenerator* explode = nullptr;
HookeForce* spring = nullptr;
DualHookForce* hook = nullptr;
std::vector<DualHookForce*> slinky;
FloatForce* water = nullptr;

double springTimer  = 0;

static const PxVec3 convexVerts[] = { PxVec3(0,20,0),PxVec3(20,0,0),PxVec3(-20,0,0),PxVec3(0,0,20),
	PxVec3(0,0,-20) };


void createCustomMesh() {

	PxConvexMeshDesc convexDesc;
	convexDesc.points.count = 5;
	convexDesc.points.stride = sizeof(PxVec3);
	convexDesc.points.data = convexVerts;
	convexDesc.flags = PxConvexFlag::eCOMPUTE_CONVEX;

	PxDefaultMemoryOutputStream buf;
	PxConvexMeshCookingResult::Enum result;


	if (!cooking->cookConvexMesh(convexDesc, buf, &result))
		std::cout << "la cague";
	//return NULL;
	PxDefaultMemoryInputData input(buf.getData(), buf.getSize());
	PxConvexMesh* convexMesh = gPhysics->createConvexMesh(input);

	PxShape* aConvexShape = CreateShape(PxConvexMeshGeometry(convexMesh), gMaterial);


	//gScene->addActor(*actor);

	RenderItem* rend = new RenderItem(aConvexShape, Color(0, 1, 0, 1));
}

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

	cooking = PxCreateCooking(PX_PHYSICS_VERSION, *gFoundation, PxCookingParams(PxTolerancesScale()));

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;

	gScene = gPhysics->createScene(sceneDesc);

	mPS = new PhysicScene(gPhysics,sceneDesc);
	
	mPS->initScene();
	//a = new Particle(Vector3(0, 0, 0), Vector3(1,0,0),0.98);
	//GeometrySpec geom1;
	//geom1.shape = SPHERE;
	//geom1.sphere.radious = 0.5;
	//geom1.box.x = 0.5;
	//geom1.box.y = 0.5;
	//geom1.box.z = 0.5;
	
	
	//parGen = new Generator(0, 4);
	////parGen->setInitialVel(Vector3(-50, 0, -50), Vector3(50, 30, 50));
	////parGen->setInitialVel(Vector3(0, -5, 0), Vector3(0, -5,0));
	//parGen->setInitalPosVar(Vector3(0,-5,0), Vector3(0,0,0));
	////parGen->setInitialVel(Vector3(-10,0,-10), Vector3(10,0, 10));
	//parGen->setParticlesPerSpawn(1);
	//parGen->setInitialPos(Vector3(0, 5, 0));
	//parGen->setParticlesAliveCond([](Particle* p) {return p->getPos().y > -100;});
	//parGen->setParticleColor(Color(0, 1, 1, 1));
	//parGen->setMassInverse(0.02);
	//parGen->setShape(geom1);
	//
	//grav = new GravityGenerator(mPS,Vector3(0,-9.8,0));
	//wind = new WindGenerator(mPS,Vector3(70, 10, 4), 1, 0,Vector3(0,10,0),Vector3(10,10,10));
	//
	//tornado = new WhirlwindGenerator(mPS, 2, 0, Vector3(2, 5, 0), Vector3(20, 60, 20), 5,10);
	
	//parGen->addForceGen(grav);
	//parGen->addForceGen(tornado);
	
	GeometrySpec geom;
	geom.shape = SPHERE;
	geom.sphere.radious = 1;
	
	//Particle* mPar = new Particle(Vector3(20, 10, 0), geom, 1,0.98, Color(1, 0, 0, 1));
	//
	////mPar->setDeathFunc([](Particle* p) {return p->getPos().y > 0; });
	//
	//mPS->addParticle(mPar);
	//
	//spring = new HookeForce(Vector3(0, 30, 0), mPar, 4, 5);
	//
	//mPar = new Particle(Vector3(20, 10, 0), geom, 1, 0.98, Color(1, 0, 0, 1));
	//
	//Particle* mPar1 = new Particle(Vector3(-20, 10, 0), geom, 1, 0.98, Color(1, 0, 0, 1));
	//
	//
	//mPS->addParticle(mPar);
	//mPS->addParticle(mPar1);
	//
	//hook = new RubberBand(mPar, mPar1,2,20);
	//mPS->addForce(hook);

	//make slinky
	Vector3 pos = Vector3(0, 40, 0);
	Particle* p1 = new Particle(pos, geom, 0, 0.98, Color(1, 0, 0, 1));

	mPS->addParticle(p1);
	for (int i = 0; i < 5; i++) {
		pos += Vector3(0, 1, 0);
		Particle* p2 = new Particle(pos, geom, 1, 0.98, Color(1, 0, 0, 1));
		mPS->addParticle(p2);
		mPS->addForce(new DualHookForce(p1, p2, 10, 8));
		p1 = p2;
	}
	//
	//resistance = new WindGenerator(mPS, Vector3(0), 0.03, 0, Vector3(0,500,0), Vector3(1000));
	//water = new FloatForce(mPS,1000, 0);
	
	//parGen->removeForce(tornado);
	//parGen->addForceGen(grav);
	//parGen->addForceGen(water);
	//parGen->addForceGen(resistance);
	
	//mPS->addForce(grav);
	//mPS->addForce(resistance);
	//mPS->addForce(wind);
	
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	springTimer += t;
	PX_UNUSED(interactive);
	//if (springTimer < 2) {
	//	spring->update(t);
	//}
	//grav->update(t);
	//wind->update(t);
	//hook->update(t);
	//tornado->update(t,mPS->getParticleList());
	//for (auto s : slinky) {
	//	s->update(t);
	//}
	//water->update(t);
	//resistance->update(t);

	mPS->updateScene(t);
	//parGen->update(t);
	//a->integrate(t);
	//gScene->simulate(t);
	//gScene->fetchResults(true);

	//parGen->clearParticles();
	mPS->clearParticles();
	
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	//gScene->release();
	delete mPS;
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
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
		explode = new ExplosionGenerator(Vector3(3,10,3),100,0.5,10000);
		//mPS->addForce(explode);
		parGen->addForceGen(explode);
		break;
	case 'H':
		springTimer = 0;
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