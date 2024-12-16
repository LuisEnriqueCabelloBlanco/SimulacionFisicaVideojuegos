#pragma once
#include "HookeForce.h"
class SpiderSling :
    public HookeForce
{
public:
    SpiderSling(Vector3 pos, physx::PxReal decaySpeed,SolidoRigido* par);
    ~SpiderSling();

    virtual void update(double dt) override;

private:
    physx::PxReal decay;
};

