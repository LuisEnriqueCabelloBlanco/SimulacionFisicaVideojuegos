#pragma once
#include "core.hpp"
#include <random>
#include <type_traits>

template<typename Ran = std::uniform_real_distribution<float>>
class Vector3Rand {
public:
	Vector3Rand() :rX(0, 1), rY(0, 1), rZ(0, 1) {

	}
	Vector3Rand(Vector3 a, Vector3 b) :rX(a.x, b.x), rY(a.y, b.y), rZ(a.z, b.z) {

	}

	~Vector3Rand() {

	}

	void setRandom(Vector3 a, Vector3 b) {
		//rX = std::uniform_real_distribution<float>(a.x, b.x);
		//if (std::is_same<Ran,std::uniform_real_distribution<float>>::value) {

		//	rX.param(Ran::param_type(min(a.x, b.x), max(a.x,b.x));
		//	rY.param(Ran::param_type(min(a.y, b.y), max(a.y,b.y));
		//	rZ.param(Ran::param_type(min(a.z, b.z), max(a.z,b.z));
		//}
		//else {
			rX.param(Ran::param_type(a.x, b.x));
			rY.param(Ran::param_type(a.y, b.y));
			rZ.param(Ran::param_type(a.z, b.z));
		//}
	}

	Vector3 operator()() {
		return Vector3(rX(gen), rY(gen), rZ(gen));
	}

private:

	std::default_random_engine gen;

	Ran rX;
	Ran rY;
	Ran rZ;
};