#pragma once
#include "ForceGenerator.h"
class WindGenerator :
    public ForceGenerator
{
public:
    WindGenerator(Vector3 wSpd, double k1, double k2) :windSpeed(wSpd), k1(k1), k2(k2) {};
    Vector3 windSpeed;
    double k1;
    double k2;
    // Heredado vía ForceGenerator
    virtual Vector3 calculateForce(Particle* par) override;
};

