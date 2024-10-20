#ifndef __CORE_HPP__
#define __CORE_HPP__

#include "../common/Common/Print.h"
#include "../common/Common/PVD.h"
#include "../common/Utils/Utils.h"

#include "Render/Render.h"
#include "Render/Camera.h"

#include <vector>

using namespace Snippets;

typedef physx::PxVec3 Vector3;
typedef physx::PxVec4 Vector4;

enum ParticleShape { SPHERE, CUBE, PLANE, CAPSULE };

struct GeometrySpec {
	ParticleShape shape;
	union {
		struct SphereSpec {
			physx::PxReal radious;
		} sphere;

		struct BoxSpec {
			physx::PxReal x;
			physx::PxReal y;
			physx::PxReal z;
		} box;

		struct CapsuleSpec {
			physx::PxReal radius;
			physx::PxReal halfHeight;
		} capsule;
	};


};

#endif