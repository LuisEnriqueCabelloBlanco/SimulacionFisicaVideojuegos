#include "Particle.h"

#define SEMIINPLICIT_EULER

using namespace physx;

Particle::Particle(Vector3& pos, Vector3& Acc,double damp):pose(pos),_vel(0),_acc(Acc),_damping(damp)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(PATICLE_SIZE)),&pose,Vector4(1, 0, 0, 1));
	
	RegisterRenderItem(renderItem);
}

Particle::Particle(Vector3& pos, double damp, ParticleShape shape, Color color) :pose(pos), _vel(0), _acc(0), _damping(damp)
{
	switch (shape)
	{
	case Particle::SPHERE:
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(PATICLE_SIZE)), &pose, color);
		break;
	case Particle::CUBE:
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(PATICLE_SIZE)), &pose, color);
		break;
	default:
		break;
	}
}

Particle::~Particle()
{
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
	pose.p += vel * dt;
	vel = vel + acc * dt;
	//acc = Vector3(0);
	vel = vel * pow(damping, dt);
#endif



}
