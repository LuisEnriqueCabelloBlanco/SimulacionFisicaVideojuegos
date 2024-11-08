#pragma once
#include "ForceGenerator.h"
class HookeForce :
    public ForceGenerator
{
public:

    HookeForce(const Vector3& pivotPos,Particle*asignedParticle, double k,double l);
    virtual void update(double dt);
    
    ~HookeForce();

private:
    Particle* particleToAplie;
    Particle* reference;
    double k;
    double l_0;
    Vector3 hookPoint;

    // Heredado vía ForceGenerator
    Vector3 calculateForce(Particle* par) override;
};

