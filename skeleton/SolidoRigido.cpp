#include "SolidoRigido.h"

SolidoRigido::SolidoRigido(Vector3 pos, GeometrySpec& geom, physx::PxPhysics* px, physx::PxScene* scene,double livetime,Vector4 color):
	mScene(scene),livetime(livetime)
{
	rigid = px->createRigidDynamic(physx::PxTransform(pos));
	physx::PxShape* pShape;

	switch (geom.shape)
	{
	case SPHERE:
		pShape = CreateShape(physx::PxSphereGeometry(geom.sphere.radious));
		break;
	case CUBE:
		pShape = CreateShape(physx::PxBoxGeometry(geom.box.x, geom.box.y, geom.box.z));
		break;
	case PLANE:
		pShape = CreateShape(physx::PxPlaneGeometry());
		break;
	case CAPSULE:
		pShape = CreateShape(physx::PxCapsuleGeometry(geom.capsule.radius, geom.capsule.halfHeight));
		break;
	default:
		break;
	}
	currentLivetime = livetime;
	rigid->attachShape(*pShape);
	mRenderItem = new RenderItem(pShape, rigid, color);
	mScene->addActor(*rigid);
	aliveCond = [this](SolidoRigido* rb) {return true;};
}

SolidoRigido::~SolidoRigido()
{
	mScene->removeActor(*rigid);
	rigid->release();
	mRenderItem->release();
	//delete mRenderItem;
}

void SolidoRigido::update(double dt)
{
	if (livetime != 0) {
		currentLivetime -= dt;
	}
	alive = aliveCond(this) && currentLivetime >= 0;
}
