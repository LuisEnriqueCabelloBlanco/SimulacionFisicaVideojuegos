#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

using namespace physx;
using Color = Vector4;

class Particle
{
public:
	//struct SphereSpec {
	//	PxReal radious;
	//};


	enum ParticleShape {SPHERE,CUBE,PLANE,CAPSULE};

	struct GeometrySpec {
		ParticleShape shape;
		union {
			struct SphereSpec{
				PxReal radious;
			} sphere;

			struct BoxSpec {
				PxReal x;
				PxReal y;
				PxReal z;
			} box;

			struct CapsuleSpec {
				PxReal radius;
				PxReal halfHeight;
			} capsule;
		};


	};



	Particle(Vector3& pos,Vector3& acc, double damp);
	Particle(Vector3& pos, GeometrySpec& geom, double damp = 0.98, Color color = Color(1, 1, 1, 1));
	~Particle();

	void integrate(double t);

	inline void accelerate(Vector3& Acc) { _acc = Acc; }

	void setColor(Vector4& color) { renderItem->color = color; }

	inline const Vector3 getVel() const { return _vel; }

private:
	const PxReal PATICLE_SIZE = 1;

	double _damping;

	Vector3 _acc;

	Vector3 _vel;

	PxTransform pose;

	RenderItem* renderItem;
};

