#pragma once
#include "ForceGenerator.h"
class WindGenerator :
    public ForceGenerator
{
public:
    WindGenerator(PhysicScene*pS, Vector3 wSpd, double k1, double k2,Vector3 center, Vector3 extent) :ForceGenerator(pS),windSpeed(wSpd), k1(k1), k2(k2) 
    {
        boxBouds = PxBounds3::centerExtents(center, extent);
        cond = [this](Particle* p) {return boxBouds.contains(p->getPos()); };
    };

    WindGenerator(PhysicScene* pS, Vector3 wSpd, double k1, double k2):ForceGenerator(pS) {

    }

    Vector3 windSpeed;
    double k1;
    double k2;
    // Heredado vía ForceGenerator
    virtual Vector3 calculateForce(Particle* par) override;
    // Heredado vía ForceGenerator
    virtual Vector3 calculateForce(SolidoRigido* rig) override;

protected:
    PxBounds3 boxBouds;

};

