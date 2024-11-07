#pragma once
#include "ForceGenerator.h"
class ExplosionGenerator :
    public ForceGenerator
{
public:
    ExplosionGenerator(const Vector3& center,float range,float timeConst,float intensity);

    // Heredado vía ForceGenerator
    Vector3 calculateForce(Particle* par) override;
private:
    Vector3 center;
    float explosionMaxRange;
    float timeConstant;
    float intensity;
    float rangeSpeed = 300;
};

