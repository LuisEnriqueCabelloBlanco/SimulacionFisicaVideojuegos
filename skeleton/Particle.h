#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include <functional>
#include <optional>

#define SEMIINPLICIT_EULER
//#define VERLET

using namespace physx;
using Color = Vector4;

class Particle
{
public:
	//struct SphereSpec {
	//	PxReal radious;
	//};
	

	Particle(){}

	Particle(const Vector3& pos,const Vector3& acc, double damp);
	Particle(const Vector3& pos,const GeometrySpec& geom,double massInverse =0, double damp = 0.98, Color color = Color(1, 1, 1, 1),double liveTime=0);
	virtual ~Particle();

	void integrate(double t);
	virtual void update(double dt);

	inline void accelerate(const Vector3& Acc) { _acc += Acc; }
	inline void addForce(Vector3 F) { _sumOfForces += F; }


	void setColor(const Vector4& color) { renderItem->color = color; }
	void setDeathFunc(const std::function<bool(Particle* par)>& f) { aliveCond = f; }

	inline const Vector3 getVel() const { return _vel; }
	inline const Vector3 getPos() const { return pose.p; }
	//returns if the particle must be alive
	inline const bool getAlive() const { return alive; }
	const double getMass() const;
	inline const physx::PxShape* getShape() { return renderItem->shape; }
protected:
	const PxReal PATICLE_SIZE = 1;

	double _damping;

	bool firstEuler = false;

	std::function<bool(Particle* p)> aliveCond;

	bool alive = true;

	double massInverse = 0;
	double livetime;
	double currentLivetime;


	Vector3 _sumOfForces;
	Vector3 _acc;
	Vector3 _vel;
#ifdef VERLET
	Vector3 prevPos;
#endif // !VERLET

	PxTransform pose;


	RenderItem* renderItem;
};

