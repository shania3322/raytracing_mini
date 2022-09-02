#ifndef SHAPE_H
#define SHAPE_H

#include "vec3.h"
#include "hittable.h"
#include <iostream>

class Material;

struct Shape {
	Shape(){}
	virtual ~Shape()=0;
};

Shape::~Shape() {
	std::cerr<<"Base Shape destructor is called\n";
}

class Sphere: public Hittable {
	public:
		Vec3 center;
		float radius;
		Material* mat_ptr;

		Sphere() {}
		Sphere(Vec3 c, float r, Material& mat): center(c), radius(r), mat_ptr{&mat} {}
		~Sphere() {}

		bool hit(Ray &p, float t_min, float t_max, Intersection &rec) const
			override;
};

bool Sphere::hit(Ray &p, float t_min, float t_max, Intersection &rec) const
{
	/* ray: P=A+t*D
	 * Sphere: center C, radius r
	 * if a ray hits circle, it should satisfy:
	 * dot((P-C),(P-C)) = r^2 ----(1)
	 *
	 * Expanding equation (1), we get a quadratic formula
	 * t^2*a + t*b + c = 0, where
	 * a = dot(D,D)
	 * b = 2*dot(D,(A-C))
	 * c = dot((A-C),(A-C)) - r^2
	 *
	 * Solve the formula for t
	 */

	Vec3 C = center;
	Vec3 A = p.origin;
	Vec3 D = p.direction;
	float a = dot(D,D);
	float b = 2.0f*dot(D, (A-C));
	float c = dot((A-C),(A-C)) - radius*radius;

	float discriminant = b*b-4.0f*a*c;
	if (discriminant < 0){
		return false;
	}

	// but we only render the closer point, thus t2 is omitted.
	float t = -1.0f/(2.0f*a)*b - sqrt(discriminant)*1.0f/(2.0f*a);
	if (t>=t_min && t<=t_max) {
		rec.t = t;
	} else {
		return false;
	}

	rec.point = p.at(rec.t);
	rec.normal = (rec.point-C)/radius;
	rec.set_normal(p);
	rec.mat_ptr = mat_ptr;
	return true;
};

class Plane: public Hittable {
	public:
		Vec3 origin;
		Vec3 normal;

		Plane() {}
		Plane(Vec3 o, Vec3 n): origin(o), normal(n) {}
		~Plane() {}

		bool hit(Ray &p, float t_min, float t_max, Intersection &rec) const override;

};

#endif
