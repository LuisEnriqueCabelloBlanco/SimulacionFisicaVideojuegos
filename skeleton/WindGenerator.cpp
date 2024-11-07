#include "WindGenerator.h"

Vector3 WindGenerator::calculateForce(Particle* par)
{
    //no hago la parte opcional ya que no tengo forma de asegurar la superficie que se opone a la direccion del viento

    Vector3 a = k1 * (windSpeed - par->getVel());
    Vector3 b = k2 * (windSpeed.magnitude() - par->getVel().magnitude()) * (windSpeed - par->getVel());

    return a+b;
}