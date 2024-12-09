#pragma once
#include <PxPhysicsAPI.h>
#include <functional>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

class SolidoRigido
{
public:
	SolidoRigido(Vector3 pos, GeometrySpec& geo,physx::PxPhysics* px,physx::PxScene* scene,Vector4 color = Vector4(1,1,1,1));
	~SolidoRigido();

	Vector3 getPose()const { return rigid->getGlobalPose().p; }
	Vector3 getVelocity()const { return rigid->getLinearVelocity(); }
	void addForce(Vector3 force) const { rigid->addForce(force); }
	void update(double dt);
	bool getAlive()const { return alive; }

private:
	bool alive = true;
	std::function<bool(SolidoRigido* p)> aliveCond;
	double livetime;
	double currentLivetime;

	physx::PxScene* mScene;
	RenderItem* mRenderItem;
	physx::PxRigidDynamic* rigid;
};

