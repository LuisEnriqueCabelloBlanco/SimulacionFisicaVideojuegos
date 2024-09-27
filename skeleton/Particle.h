#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

using namespace physx;
using Color = Vector4;

class Particle
{
public:
	enum ParticleShape {SPHERE,CUBE};

	Particle(Vector3& pos,Vector3& acc, double damp);
	Particle(Vector3& pos, double damp, ParticleShape shape, Color color);
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

