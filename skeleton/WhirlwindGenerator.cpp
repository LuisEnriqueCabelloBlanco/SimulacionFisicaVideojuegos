#include "WhirlwindGenerator.h"

Vector3 WhirlwindGenerator::calculateForce(Particle* par)
{
    Vector3 p =par->getPos();
    Vector3 c = boxBouds.getCenter();
    windSpeed = K*Vector3(-(p.z-c.z),ySpeed/*-(p.y-c.y)*/, (p.x - c.x));
    return WindGenerator::calculateForce(par);
}
