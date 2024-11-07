#pragma once
#include "ForceGenerator.h"
class ExplosionGenerator :
    public ForceGenerator
{
public:
    ExplosionGenerator();

    // Heredado v�a ForceGenerator
    Vector3 calculateForce(Particle* par) override;
private:
    Vector3 center;
    float explosionMaxRange;
    float timeConstant;
    float intensity;
};

