#pragma once
#include "ForceGenerator.h"
class ExplosionGenerator :
    public ForceGenerator
{
public:
    ExplosionGenerator(const Vector3& center,float range,float timeConst,float intensity);

    // Heredado vía ForceGenerator
    Vector3 calculateForce(Particle* par) override;
    Vector3 calculateForce(SolidoRigido* rig) override;
private:
    Vector3 center;
    float explosionMaxRange;
    float timeConstant;
    float intensity;
    float rangeSpeed = 300;

    // Heredado vía ForceGenerator
};

