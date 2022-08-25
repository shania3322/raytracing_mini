#pragma once

#include "vec3.h"
#include "ray.h"

struct Intersection {
	Vec3 point;
	Vec3 normal;
	float t;
	bool frontface;

	void set_normal(Ray &r);
};

void Intersection::set_normal(Ray &r) {
	if (dot(r.direction, normal)<0.0f){
		frontface = true;
	}
	else {
		normal = -normal;
		frontface = false;
	}
}

class Hittable {
	public:
		virtual bool hit(Ray &r, float t_min, float t_max, Intersection &rec) const = 0;
};

class IntersectList {

};
