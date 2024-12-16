#pragma once
#include "SolidoRigido.h"

class PhysicScene;

class SpiderWeb :
    public SolidoRigido
{
public:
    SpiderWeb(Vector3 pos, Vector3 speed, PhysicScene* mPs, physx::PxScene* sc,bool t);

    void onCollision(physx::PxRigidActor* act) override;

    ~SpiderWeb();

private:
    PhysicScene* mPS;
    static physx::PxReal constexpr rad = 0.1;
    static physx::PxReal constexpr l = 0.2;
    bool t;
};

