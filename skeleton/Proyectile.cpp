#include "Proyectile.h"

Proyectile::Proyectile(double massInverser,const Vector3& pos,const GeometrySpec& geom, const Vector3& initialSpeed,double liveTime , Color color, double damp):
	Particle(pos,geom,damp,color,liveTime),massInverse(massInverse)
{
	_vel = initialSpeed;
}

void Proyectile::addForce(const Vector3& force)
{
	_acc += force * massInverse;
}
