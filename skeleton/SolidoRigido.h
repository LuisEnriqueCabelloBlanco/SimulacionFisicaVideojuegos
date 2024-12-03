#pragma once
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

class SolidoRigido
{
public:
	SolidoRigido(Vector3 pos, GeometrySpec& geo,physx::PxPhysics* px,physx::PxScene* scene);
	~SolidoRigido();
private:
	physx::PxScene* mScene;
	RenderItem* mRenderItem;
	physx::PxRigidDynamic* rigid;
};

