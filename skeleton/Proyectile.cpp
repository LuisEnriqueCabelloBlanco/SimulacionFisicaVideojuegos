#include "Proyectile.h"

Proyectile::Proyectile(double mass,const Vector3& pos,const GeometrySpec& geom, const Vector3& initialSpeed, double damp, Color color):
	Particle(pos,geom,damp,color),mass(mass)
{
	_vel = initialSpeed;
}

void Proyectile::addForce(const Vector3& force)
{
	_acc += force / mass;
}
