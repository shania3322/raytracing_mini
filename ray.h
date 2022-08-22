#pragma once

#include "vec3.h"

class Ray {
	public:
		Vec3 origin;
		Vec3 direction;

		Ray() {}
		Ray(const Vec3 o, const Vec3 d):
			origin(o.x,o.y,o.z), direction(d.x,d.y,d.z) {}

		Vec3 at(float t) {
			return origin+t*direction;
		}
};

