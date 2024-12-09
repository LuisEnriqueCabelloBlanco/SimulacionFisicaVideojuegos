#include "GravityGenerator.h"

Vector3 GravityGenerator::calculateForce(Particle* par)
{
    return gravityAcc*par->getMass();
}

Vector3 GravityGenerator::calculateForce(SolidoRigido* rig)
{
    return Vector3();
}
