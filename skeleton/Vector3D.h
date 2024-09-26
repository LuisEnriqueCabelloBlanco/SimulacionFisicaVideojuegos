#pragma once
class Vector3D
{
public:
	float x;
	float y;
	float z;

	Vector3D(float x = 0, float y = 0, float z=0) :x(x), y(y), z(z) {};

	inline Vector3D add(const Vector3D& v) {
		return Vector3D(x+v.x,y+v.y,z+v.z);
	}
	
	inline Vector3D subb(const Vector3D& v) {
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}

	float magnitude() const;

	Vector3D normalize();

	float dot(const Vector3D& v);

	Vector3D operator+(const Vector3D& v);
	Vector3D operator-(const Vector3D& v);
	Vector3D operator*(float sc);
	Vector3D operator*(const Vector3D& v);

};

Vector3D operator*(float sc, const Vector3D& v) {
	return Vector3D(v.x * sc, v.y * sc, v.z * sc);
};



