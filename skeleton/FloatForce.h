#pragma once
#include "ForceGenerator.h"
class FloatForce :
    public ForceGenerator
{
public:

    FloatForce(double density, double waterHeight);
    FloatForce(PhysicScene* mps, double density, double waterHeight);
    ~FloatForce() {};
private:

    // Heredado vía ForceGenerator
    Vector3 calculateForce(Particle* par) override;

    double _liquid_density;
    double immersed;
    double h0;
};

