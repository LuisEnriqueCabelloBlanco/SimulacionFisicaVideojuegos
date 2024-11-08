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
    //particula a la que aplicar el muelle
    Particle* particleToAplie;
    //referencia visual
    Particle* reference;
    //coeficiente de elasticidad
    double k;
    //longitud en reposo
    double l_0;
    Vector3 hookPoint;

    // Heredado vía ForceGenerator
    Vector3 calculateForce(Particle* par) override;
};

