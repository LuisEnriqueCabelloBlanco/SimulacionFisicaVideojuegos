#include "SpiderWeb.h"
#include "PhysicScene.h"

SpiderWeb::SpiderWeb(Vector3 pos, Vector3 speed, PhysicScene* mPs, physx::PxScene* sc,bool type):
	SolidoRigido(pos,GeometrySpec(0.2),&sc->getPhysics(), sc, 5, Color(1, 1, 1, 0.5)), mPS(mPs)
{
	PxReal mass = 0.001;
	rigid->setLinearVelocity(speed);
	rigid->setName("Web");
	PxReal zyVal = (1 / 12) * mass * (3*(rad*rad)+l*l);
	rigid->setMassSpaceInertiaTensor(Vector3(0.5 * mass * rad * rad,zyVal,zyVal));
	aliveCond = [](SolidoRigido* rb) {return rb->getRigid()->getGlobalPose().p.y > 1; };
	mPS->addParticle(this);
	t = type;
}

void SpiderWeb::onCollision(physx::PxRigidActor* act)
{
	if (act->userData == nullptr) {
		mPS->createWeb(rigid->getGlobalPose().p,t);
		//kill the particle
		currentLivetime = -1;
	}
}

SpiderWeb::~SpiderWeb()
{
	
}
