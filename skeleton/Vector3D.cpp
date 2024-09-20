#include "Vector3D.h"
#include <cmath>

float Vector3D::magnitude()
{
    return sqrt(x*x+y*y+z*z);
}

Vector3D Vector3D::normalize()
{
    float mod = magnitude();

    return Vector3D(x/mod,y/mod,z/mod);
}

float Vector3D::dot(const Vector3D& v)
{
    return x*v.x+y*v.y+z*v.z;
}

Vector3D Vector3D::operator+(const Vector3D& v)
{
    return this->add(v);
}

Vector3D Vector3D::operator-(const Vector3D& v)
{
    return this->subb(v);
}

Vector3D Vector3D::operator*(float sc)
{
    return Vector3D(x*sc,y*sc,z*sc);
}

Vector3D Vector3D::operator*(const Vector3D& v)
{
    return this->dot(v);
}


