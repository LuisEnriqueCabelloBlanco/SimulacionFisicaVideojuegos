#include "FloatForce.h"

FloatForce::FloatForce(double density, double waterHeight):FloatForce(nullptr,density,waterHeight)
{
    
}

FloatForce::FloatForce(PhysicScene* mps, double density, double waterHeight) :ForceGenerator(mps),
    _liquid_density(density), h0(waterHeight)
{

}

Vector3 FloatForce::calculateForce(Particle* par)
{
    double h = par->getPos().y;
    double volume = par->getBase()*par->getHeight();

    if ((h - h0) > (par->getHeight() * 0.5)) 
    {
        immersed = 0.0;
    }
    else if ((h0 - h) > (par->getHeight() * 0.5)) {
        immersed = 1.0;
    }
    else {
        immersed = (h0-h) / par->getHeight() + 0.5;
    }

    double fy = _liquid_density * volume * immersed * 9.8;

    return Vector3(0,fy,0);
}
