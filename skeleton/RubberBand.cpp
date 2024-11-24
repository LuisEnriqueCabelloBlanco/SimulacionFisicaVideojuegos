#include "RubberBand.h"

RubberBand::RubberBand(Particle* a, Particle* b, double k, double l):DualHookForce(a,b,k,l)
{

}

void RubberBand::update(double dt)
{
	if ((pA->getPos()-pB->getPos()).magnitude() > l_0) {
		DualHookForce::update(dt);
	}
}
