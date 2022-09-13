#include "vec3.h"
#include "color.h"
#include "ray.h"
//#include "test.h"
#include "hittable.h"
#include "shape.h"
#include "camera.h"
#include "util.h"
#include "material.h"

//#define ENABLE_TEST

#include <iostream>
#include <tuple>

bool Lambertian::scattered(Ray &in, Ray &scattered,
		Vec3 &attenuation, Intersection &rec) const {
	Vec3 s = rec.point+rec.normal+random_unit_vector();
	Vec3 direction = s-rec.point;
	if (near_zero(direction)) {
		direction = rec.normal;
	}
	scattered = Ray(rec.point+0.001f*rec.normal, direction);
	attenuation = static_cast<Lambertian*>(rec.mat_ptr)->albedo;
	return true;
}

bool Metal::scattered(Ray &in, Ray &scattered,
		Vec3 &attenuation, Intersection &rec) const {
	Vec3 direction = reflected(in.direction, rec.normal);
	Vec3 shift = fuzz*random_in_unit_sphere();
	scattered = Ray(rec.point+0.001f*rec.normal, direction+shift);
	attenuation = static_cast<Metal*>(rec.mat_ptr)->albedo;
	return true;
}

bool Dielectrics::scattered(Ray &in, Ray &scattered,
		Vec3 &attenuation, Intersection &rec) const {
	/* Snell's law and Fresnel equations.
	 * Snell's law:
	 * eta*sin(theta) = eta_prime*sin(theta_prime)
	 * eta, eta_prime: refractive indices of materials
	 *
	 * Fresnel equations:
	 * F_reflect = 1/2*(F_reflect_parallel + F_reflect_orthogonal)
	 * F_transmit +F_reflect = 1
	 * For simplicity, we implement Snell's law only for now. i.e. either relect
	 * or refract.
	 *
	 * Also, we assume one medium is always air and we treat is as vaccum which
	 * has relective index of 1.0 (eta = v_in/v_out).
	 */
	attenuation = Vec3(1.0f,1.0f,1.0f);
	float bias = 0.001f;

	float refract_in = 1.0f;
	float refract_out = static_cast<Dielectrics*>(rec.mat_ptr)->refract_index;
	float roi = refract_in/refract_out;
	if (!rec.frontface) {
		roi = 1.0f/roi;
	}

	Vec3 refract_r = refract(in.direction, rec.normal, roi);
	//bool if_reflect = fresnel(in, rec, roi)>random_float();
	bool if_reflect = schlick(in, rec, roi)>random_float();

	if ((refract_r == Vec3(0.0f,0.0f,0.0f))||if_reflect) {
		// only reflection exists
		Vec3 direction = reflected(in.direction, rec.normal);
		scattered = Ray(rec.point+bias*rec.normal, direction);
	} else {
		// may refract, randomly choose to refract or reflect
		scattered = Ray(rec.point+bias*(-rec.normal), refract_r);
	}
	return true;
}

float Dielectrics::fresnel(Ray &in, Intersection &rec, float roi) const
{
	float cos_theta = cosTheta(-in.direction, rec.normal);
	float s = roi*sqrt(1-cos_theta*cos_theta);
	float cos_theta_prime = sqrt(1.0f - s*s);
	float t1 = (cos_theta - roi*cos_theta_prime)/
		(cos_theta + roi*cos_theta_prime);
	float t2 = (roi*cos_theta_prime - cos_theta)/
		(roi*cos_theta_prime + cos_theta);
	return 1.0f/2.0f*(t1*t1+t2*t2);
}

float Dielectrics::schlick(Ray &in, Intersection &rec, float roi) const
{
	float r0 = (roi-1)/(roi+1);
	float r1 = r0*r0;
	float cos_theta = cosTheta(-in.direction, rec.normal);
	return (r1 + (1.0f-r1)*pow((1.0f-cos_theta),5.0f));
}

Color ray_color(Ray &r, HittableList &obj_list, int max_depth) {
	if (max_depth<0) {
		return Color(0.0f, 0.0f, 0.0f);
	}

	Intersection rec = Intersection();
	bool if_hit = obj_list.hit(r,0.001f,999999.0f,rec);

	// When hit an object computer reflect direction
	if (if_hit) {
		Ray r_next;
		Vec3 attenuation;
		if (rec.mat_ptr->scattered(r, r_next, attenuation, rec))
		{
			max_depth -=1;
			return attenuation*ray_color(r_next, obj_list, max_depth);
		}
		return Color(0.0f, 0.0f,0.0f);
	}
	else {
		Vec3 unit = unit_vector(r.direction-r.origin);
		float t = (unit.y+1.0)*0.5f;
		return (1.0f-t)*Color(1.0f,1.0f,1.0f)+t*Color(0.5,0.7,1.0f);
	}
}

#ifndef ENABLE_TEST
int main() {
	// Image
	const float aspect_ratio = 16.0f/9.0f;
	const int img_width = 512;
	const int img_height = int(float(img_width)/aspect_ratio);
	const int samples_per_pixel = 10;
	const int max_depth = 50;
	Lambertian diffuse1= Lambertian(Vec3(0.8f,0.8f,0.0f));
	Lambertian diffuse2 = Lambertian(Vec3(0.1f,0.2f,0.5f));
	Metal metal1 = Metal(Vec3(0.8f,0.6f,0.2f), 0.0f);
	Metal metal2 = Metal(Vec3(0.8f,0.8f,0.2f), 0.8f);
	Dielectrics glass1 = Dielectrics(1.5);
	Dielectrics glass2 = Dielectrics(1.5);

	//camera
	Vec3 lookfrom = Vec3(3.0f, 3.0f, 2.0f);
	Vec3 lookat = Vec3(0.0f,0.0f,-1.0f);
	Vec3 vup = Vec3(0.0f,1.0f,0.0f);
	float aperture_radius = 2.0f;
	float focus_distance = (lookfrom-lookat).length();
	Camera camera(lookfrom,lookat,vup, 20.0f, aspect_ratio,
			aperture_radius, focus_distance);

	// Render
	std::cout<<"P3\n"<<img_width<<" "<<img_height<<"\n255\n";

	HittableList obj_list;
	Sphere c3 = Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f, diffuse1);
	Sphere c4 = Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f, diffuse2);
	Sphere c1 = Sphere(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, glass1);
	Sphere c2 = Sphere(Vec3(-1.0f, 0.0f, -1.0f), -0.45f, glass1);
	Sphere c5 = Sphere(Vec3(1.0f, 0.0f, -1.0f), 0.5f, metal1);
	obj_list.add(&c1);
	obj_list.add(&c2);
	obj_list.add(&c3);
	obj_list.add(&c4);
	obj_list.add(&c5);

	for (int i=img_height-1; i>=0; --i){
		std::cerr<<"\rScanlines remaining:"<<i<<std::flush;
		for (int j=0; j<=img_width-1; ++j){
			float x = float(j)/float(img_width-1);
			float y = float(i)/float(img_height-1);
			Color acc_color;
			for (int n=0; n<samples_per_pixel; ++n) {
				float du = random_float()*(1.0f/float(img_width-1));
				float dv = random_float()*(1.0f/float(img_height-1));
				Ray r = camera.get_ray(x+du,y+dv);
				Color color = ray_color(r, obj_list, max_depth);
				acc_color = acc_color+color;
			}

			write_color(std::cout, acc_color, samples_per_pixel);
		}
	}
	std::cerr<<"\nDone.\n";
	return 0;
}
#else
int main()
{
	Test myTest = Test();
	//myTest.runTest();
	//myTest.test_shape();
}
#endif
