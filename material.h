#pragma once
#include "util.h"


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
		float fuzz;

	public:
		Metal(const Vec3 r, float f): albedo(r), fuzz(f<1.0f? f:1.0f){}
		bool scattered(Ray &in, Ray &scattered, Vec3 &attenuation, Intersection &rec)
			const override;
};

/*Materials for water, glass and diamonds dielectrics,
 *i.e. has both light reflection and refraction.
 */
class Dielectrics: public Material {
	public:
		float refract_index;

	public:
		Dielectrics(const float refract): refract_index(refract) {}
		bool scattered(Ray &in, Ray &scattered, Vec3 &attenuation, Intersection &rec)
			const	override;

	private:
		float fresnel(Ray &in, Intersection &rec, float roi) const;
		float schlick(Ray &in, Intersection &rec, float roi) const;
};
