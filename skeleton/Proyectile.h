#pragma once
#include "Particle.h"

/// <summary>
/// A Particle sensible to forces aplied to it
/// </summary>
class Proyectile :
    public Particle
{
public:
    Proyectile(double massinverse,const Vector3& pos,const GeometrySpec& geom, const Vector3& initialSpeed = Vector3(0,0,0),double liveTime = 0.0, Color color = Color(1, 1, 1, 1), double damp = 0.98);
    void addForce(const Vector3& force);
private:
    //proyectile mass in kg
    double massInverse;
};

