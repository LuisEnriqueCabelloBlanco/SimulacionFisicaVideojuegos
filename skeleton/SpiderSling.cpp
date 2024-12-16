#include "SpiderSling.h"

SpiderSling::SpiderSling(Vector3 pos, physx::PxReal decaySpeed, SolidoRigido* par) :
	HookeForce(pos, par, 200, 3),decay(decaySpeed)
{

}

SpiderSling::~SpiderSling()
{

}

void SpiderSling::update(double dt)
{
	l_0 += decay * dt;
	HookeForce::update(dt);
}
