#include "WhirlwindGenerator.h"
#include "SolidoRigido.h"
Vector3 WhirlwindGenerator::calculateForce(Particle* par)
{
    Vector3 p =par->getPos();
    Vector3 c = boxBouds.getCenter();
    windSpeed = K*Vector3(-(p.z-c.z),ySpeed/*-(p.y-c.y)*/, (p.x - c.x));
    return WindGenerator::calculateForce(par);
}

Vector3 WhirlwindGenerator::calculateForce(SolidoRigido* rig)
{
    Vector3 p = rig->getPose();
    Vector3 c = boxBouds.getCenter();
    windSpeed = K * Vector3(-(p.z - c.z), ySpeed/*-(p.y-c.y)*/, (p.x - c.x));
    return WindGenerator::calculateForce(rig);
}
