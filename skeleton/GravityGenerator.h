#pragma once
#include "ForceGenerator.h"
class GravityGenerator :
    public ForceGenerator
{
public:
    GravityGenerator(Vector3 gravity = Vector3(0,-9.8,0)) :ForceGenerator() {
        gravityAcc = gravity;
    }

    // Heredado vía ForceGenerator
    Vector3 calculateForce(Particle* par) override;

private:
    Vector3 gravityAcc;

};

