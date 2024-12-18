#pragma once
#include <PxPhysicsAPI.h>
#include <functional>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"


class SolidoRigido
{
public:
	SolidoRigido(Vector3 pos, GeometrySpec& geo,physx::PxPhysics* px,physx::PxScene* scene,double livetime =0,Vector4 color = Vector4(1,1,1,1));
	virtual ~SolidoRigido();

	Vector3 getPose()const { return rigid->getGlobalPose().p; }
	Vector3 getVelocity()const { return rigid->getLinearVelocity(); }
	void addForce(Vector3 force) const { rigid->addForce(force); }
	void update(double dt);
	bool getAlive()const { return alive; }

	void setDeathFunc(const std::function<bool(SolidoRigido* p)>& f) { aliveCond = f; }
	void setMass(physx::PxReal mass) { physx::PxRigidBodyExt::updateMassAndInertia(*rigid, mass); }
	void setVelocity(Vector3 vel) { rigid->setLinearVelocity(vel); }
	void unrender() { mRenderItem->release(); }

	virtual void onCollision(physx::PxRigidActor* act);

	physx::PxRigidDynamic* getRigid() { return rigid; }
protected:
	bool alive = true;
	std::function<bool(SolidoRigido* p)> aliveCond;
	double currentLivetime;
	double livetime;

	physx::PxScene* mScene;
	RenderItem* mRenderItem;
	physx::PxRigidDynamic* rigid;
};

