#include "GeneradorParticulas.h"
#include "Proyectile.h"
#include "PhysicScene.h"

void GeneradorParticulas::update(double dt)
{
	currentTime += dt;
	addParticle();
}

void GeneradorParticulas::addParticle()
{
	if (currentTime > nextSpawnTime) {
		GeometrySpec geom;
		geom.shape = SPHERE;
		geom.sphere.radious = 1;
		//spawn particle magic

		Proyectile* pr = mPS->createProyectile(0.5, position(), initVel(),geom);
		pr->accelerate(Vector3(0,-9.8,0));

		nextSpawnTime = particleRate + uRandGenTime(gen);
		currentTime = 0;
	}
}
