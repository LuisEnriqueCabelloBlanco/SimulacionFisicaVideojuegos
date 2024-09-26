#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

using namespace physx;
class Particle
{
public:
	Particle(Vector3& pos,Vector3& acc, double damp);
	~Particle();

	void integrate(double t);

	inline void accelerate(Vector3& Acc) { acc = Acc; }

	void setColor(Vector4& color) { renderItem->color = color; }

private:
	const PxReal PATICLE_SIZE = 1;

	double damping;

	Vector3 acc;

	Vector3 vel;

	PxTransform pose;

	RenderItem* renderItem;
};

