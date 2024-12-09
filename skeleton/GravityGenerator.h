#pragma once
#include "ForceGenerator.h"
class GravityGenerator :
    public ForceGenerator
{
public:
    GravityGenerator(PhysicScene*pS,Vector3 gravity = Vector3(0,-9.8,0)) :ForceGenerator(pS) {
        gravityAcc = gravity;
    }

    // Heredado v�a ForceGenerator
    Vector3 calculateForce(Particle* par) override;

private:
    Vector3 gravityAcc;


    // Heredado v�a ForceGenerator
    Vector3 calculateForce(SolidoRigido* rig) override;

};

