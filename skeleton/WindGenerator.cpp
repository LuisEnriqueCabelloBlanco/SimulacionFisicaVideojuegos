#include "WindGenerator.h"

Vector3 WindGenerator::calculateForce(Particle* par)
{
    Vector3 a = k1 * (windSpeed - par->getVel());
    Vector3 b = k2 * (windSpeed.magnitude() - par->getVel().magnitude()) * (windSpeed - par->getVel());

    return a+b;
}
