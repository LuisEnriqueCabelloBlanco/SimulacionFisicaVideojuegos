#include "Particle.h"

using namespace physx;

Particle::Particle(Vector3& pos, Vector3& Acc):pose(pos),vel(0),acc(Acc)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(PATICLE_SIZE)),&pose,Vector4(1, 0, 0, 1));
	
	RegisterRenderItem(renderItem);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void Particle::integrate(double dt)
{
	vel += acc * dt;
	pose.p += vel*dt;
	acc = Vector3(0);
}
