#pragma once
#include "Particle.h"

/// <summary>
/// A Particle sensible to forces aplied to it
/// </summary>
class Proyectile :
    public Particle
{
public:
    Proyectile(double mass,const Vector3& pos,const GeometrySpec& geom, const Vector3& initialSpeed = Vector3(0,0,0), double damp = 0.98, Color color = Color(1, 1, 1, 1));
    void addForce(const Vector3& force);
private:
    //proyectile mass in kg
    double mass;
};

