#include "Proyectile.h"

Proyectile::Proyectile(double massInverser,const Vector3& pos,const GeometrySpec& geom, const Vector3& initialSpeed, double damp, Color color):
	Particle(pos,geom,damp,color),massInverse(massInverse)
{
	_vel = initialSpeed;
}

void Proyectile::addForce(const Vector3& force)
{
	_acc += force * massInverse;
}
