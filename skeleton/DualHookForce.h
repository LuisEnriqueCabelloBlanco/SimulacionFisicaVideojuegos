#pragma once
#include "ForceGenerator.h"
class DualHookForce :
    public ForceGenerator
{
public:

    DualHookForce(Particle* a,Particle* b, double k,double l);
    
    ~DualHookForce() {};

    virtual void update(double dt) override;
protected:

    Particle* pA;

    Particle* pB;

    //coeficiente de elasticidad
    double k;
    //longitud en reposo
    double l_0;

    // Heredado vía ForceGenerator
    Vector3 calculateForce(Particle* par) override;
    
    Vector3 calculateSpringForce(Particle* A, Particle* B);


    // Heredado vía ForceGenerator
    Vector3 calculateForce(SolidoRigido* rig) override;

};

