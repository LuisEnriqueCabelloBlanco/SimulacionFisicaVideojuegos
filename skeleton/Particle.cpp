#include "Particle.h"

#define SEMIINPLICIT_EULER

using namespace physx;

Particle::Particle(const Vector3& pos,const Vector3& Acc,double damp):pose(pos),_vel(0),_acc(Acc),_damping(damp)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(PATICLE_SIZE)),&pose,Vector4(1, 0, 0, 1));
}

Particle::Particle(const Vector3& pos,const GeometrySpec& geom, double damp, Color color)
	:pose(pos), _vel(0), _acc(0), _damping(damp)
{
	PxShape* pShape;

	switch (geom.shape)
	{
	case Particle::SPHERE:
		pShape = CreateShape(PxSphereGeometry(geom.sphere.radious));
		break;
	case Particle::CUBE:
		pShape = CreateShape(PxBoxGeometry(geom.box.x,geom.box.y,geom.box.z));
		break;
	case Particle::PLANE:
		pShape = CreateShape(PxPlaneGeometry());
		break;
	case Particle::CAPSULE:
		pShape = CreateShape(PxCapsuleGeometry(geom.capsule.radius,geom.capsule.halfHeight));
		break;
	default:
		break;
	}

	renderItem = new RenderItem(pShape,&pose, color);
}

Particle::~Particle()
{
	//Si se emplea deregister render item el programa de un error de iterador al cerrarlo
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void Particle::integrate(double dt)
{
#ifdef SEMIINPLICIT_EULER
	_vel = _vel + _acc * dt;
	pose.p += _vel*dt;
	//acc = Vector3(0);
	_vel = _vel * pow(_damping, dt);
#else
	pose.p += _vel * dt;
	_vel = _vel + _acc * dt;
	//acc = Vector3(0);
	_vel = _vel * pow(_damping, dt);
#endif



}
