#include <vector>
#include "vec3.h"
#include "ray.h"
//#include "shape.h"
#include "util.h"

#ifndef HITTABLE_H
#define HITTABLE_H

class Material;

struct Intersection {
	Vec3 point;
	Vec3 normal;
	float t;
	bool frontface;
	Material* mat_ptr;

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

class HittableList: public Hittable {
	public:
		std::vector<Hittable*> objects;

	public:
		HittableList() {}

		void add(Hittable* obj) {
			objects.push_back(obj);
		}

		void clear() {
			objects.clear();
		}

		bool hit(Ray &r, float t_min, float t_max, Intersection &rec) const
			override;
};

bool HittableList::hit(Ray &r, float t_min, float t_max, Intersection &rec) const {
	// When ray hits multiple objects, store the closest intersection.
	// At the end, only one set of intersections on viewport is saved.
	//Intersection temp;
	float closest_t = t_max;
	bool if_hit = false;

	//When shooting a ray, check each object in the scene and find if anywhere is hit.
	for (const auto &obj : objects) {
		if (obj->hit(r, t_min, closest_t, rec)) {
			if_hit = true;
			closest_t = rec.t;
			//rec = temp;
		}
	}

	return if_hit;
}
#endif
