#pragma once
#include "WindGenerator.h"
class WhirlwindGenerator :
    public WindGenerator
{
public:
    WhirlwindGenerator(PhysicScene* pS, double k1, double k2, Vector3 center, Vector3 extent,double K,double ySpeed) :WindGenerator(pS,Vector3(0), k1, k2, center, extent) ,K(K),ySpeed(ySpeed){

    }
    virtual Vector3 calculateForce(Particle* par) override;
private:
    double K;
    double ySpeed;
};

