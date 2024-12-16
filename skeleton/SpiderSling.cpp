#include "SpiderSling.h"

SpiderSling::SpiderSling(Vector3 pos, physx::PxReal decaySpeed, SolidoRigido* par,double k) :
	HookeForce(pos, par, k, 0.5),decay(decaySpeed)
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
