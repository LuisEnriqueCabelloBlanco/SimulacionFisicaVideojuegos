#pragma once
#include "DualHookForce.h"
class RubberBand :
    public DualHookForce
{
public:

    RubberBand(Particle* a, Particle* b, double k, double l);
    ~RubberBand() {};

    virtual void update(double dt) override;
};

