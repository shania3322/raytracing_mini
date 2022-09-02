#pragma once
#include "util.h"

#define PI 3.14159265358979

struct Intersection;

class Material {
	public:
		virtual bool scattered(Ray &in, Ray &scattered, Vec3 &attenuation, Intersection &rec) const = 0;
};

class Lambertian: public Material {
	/* albedo represent the ratio of the reflected light
	 * over the amount of incident light. We assign reflection rate for r,g,b
	 * channel seperately.
	 */
	public:
		Vec3 albedo;

	public:
		Lambertian(const Vec3 r): albedo(r){}
		bool scattered(Ray &in, Ray &scattered, Vec3 &attenuation, Intersection &rec)
			const override;
};


class Metal: public Material {
	public:
		Vec3 albedo;

	public:
		Metal(const Vec3 r): albedo(r){}
		bool scattered(Ray &in, Ray &scattered, Vec3 &attenuation, Intersection &rec)
			const override;
};


