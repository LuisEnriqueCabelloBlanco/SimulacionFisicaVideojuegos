#include "Particle.h"
#include <iostream>


using namespace physx;

Particle::Particle(const Vector3& pos,const Vector3& Acc,double damp):pose(pos),_acc(Acc),_damping(damp), _vel(0)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(PATICLE_SIZE)),&pose,Vector4(1, 0, 0, 1));
}

Particle::Particle(const Vector3& pos,const GeometrySpec& geom, double damp, Color color, double liveTime)
	:pose(pos), _acc(0), _damping(damp),_vel(0),livetime(liveTime)
{
	currentLivetime = liveTime;
	PxShape* pShape;

	switch (geom.shape)
	{
	case SPHERE:
		pShape = CreateShape(PxSphereGeometry(geom.sphere.radious));
		break;
	case CUBE:
		pShape = CreateShape(PxBoxGeometry(geom.box.x,geom.box.y,geom.box.z));
		break;
	case PLANE:
		pShape = CreateShape(PxPlaneGeometry());
		break;
	case CAPSULE:
		pShape = CreateShape(PxCapsuleGeometry(geom.capsule.radius,geom.capsule.halfHeight));
		break;
	default:
		break;
	}

	renderItem = new RenderItem(pShape,&pose, color);
	aliveCond = [](Particle* p) {return true; };
}

Particle::~Particle()
{
	//Si se emplea deregister render item el programa de un error de iterador al cerrarlo
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void Particle::integrate(double dt)
{

#ifdef VERLET
	if (firstEuler&&_acc.magnitudeSquared() > 0) {
		Vector3 aux = pose.p;
		pose.p = pose.p * 2 - prevPos + _acc * dt;
		prevPos = aux;
	}
	else {
		prevPos = pose.p;
		pose.p += _vel * dt;
		firstEuler = true;
	}

#elif defined(SEMIINPLICIT_EULER)
	_vel = _vel + _acc * dt;
	pose.p += _vel * dt;
	//acc = Vector3(0);
	_vel = _vel * pow(_damping, dt);
#else
	pose.p += _vel * dt;
	_vel = _vel + _acc * dt;
	//acc = Vector3(0);
	_vel = _vel * pow(_damping, dt);
#endif
	



}

void Particle::update(double dt)
{
	integrate(dt);
	if (livetime != 0) {
		currentLivetime -= dt;
	}
	alive = aliveCond(this) && currentLivetime >=0;
}
