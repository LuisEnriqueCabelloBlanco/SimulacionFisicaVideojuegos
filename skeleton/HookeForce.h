#pragma once
#include "ForceGenerator.h"
class HookeForce :
    public ForceGenerator
{
public:

    HookeForce(const Vector3& pivotPos,Particle*asignedParticle, double k,double l);
    HookeForce(const Vector3& pivotPos,SolidoRigido*asignedParticle, double k,double l);
    virtual void update(double dt);
    
    ~HookeForce();

private:
    SolidoRigido* particeRb = nullptr;
    //particula a la que aplicar el muelle
    Particle* particleToAplie = nullptr;
    //referencia visual
    Particle* reference;
    //coeficiente de elasticidad
    double k;
    //longitud en reposo
    double l_0;
    Vector3 hookPoint;

    // Heredado vía ForceGenerator
    Vector3 calculateForce(Particle* par) override;
    Vector3 calculateForce(SolidoRigido* rig) override;
};

