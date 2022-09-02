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

bool Lambertian::scattered(Ray &in, Ray &scattered,
		Vec3 &attenuation, Intersection &rec) const {
	Vec3 s = rec.point+rec.normal+random_unit_vector();
	Vec3 direction = s-rec.point;
	if (near_zero(direction)) {
		direction = rec.normal;
	}
	scattered = Ray(rec.point, direction);
	attenuation = static_cast<Lambertian*>(rec.mat_ptr)->albedo;
	return true;
}


bool Metal::scattered(Ray &in, Ray &scattered,
		Vec3 &attenuation, Intersection &rec) const {
	Vec3 direction = reflected(in.direction, rec.normal);
	scattered = Ray(rec.point, direction);
	attenuation = static_cast<Metal*>(rec.mat_ptr)->albedo;
	return true;
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
		//Vec3 s = rec.point+rec.normal+random_unit_vector();
		//Ray next_r = Ray(rec.point, (s-rec.point));
		//max_depth -= 1;
		////TODO: add material rec.mat_ptr->members
		//return 0.5*ray_color(next_r, obj_list, max_depth);
		////return 0.5*(unit_vector(rec.normal)+Vec3(1.0f,1.0f,1.0f));
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
	Lambertian diffuse1= Lambertian(Vec3(0.5f,0.8f,0.5f));
	Lambertian diffuse2 = Lambertian(Vec3(0.3f,0.3f,0.3f));
	Metal metal1 = Metal(Vec3(0.5f,0.2f,0.5f));
	Metal metal2 = Metal(Vec3(0.8f,0.8f,0.2f));

	Camera camera;

	// Render
	std::cout<<"P3\n"<<img_width<<" "<<img_height<<"\n255\n";

	HittableList obj_list;
	Sphere c1 = Sphere(Vec3(-0.6f, 0.0f, -1.0f), 0.3f, metal1);
	Sphere c2 = Sphere(Vec3(0.6f, 0.0f, -1.0f), 0.3f, metal2);
	Sphere c3 = Sphere(Vec3(0.0f,-100.3f,-1.0f), 100.0f, diffuse1);
	Sphere c4 = Sphere(Vec3(0.0f,0.0f,-1.0f), 0.3f, diffuse2);
	obj_list.add(&c1);
	obj_list.add(&c2);
	obj_list.add(&c3);
	obj_list.add(&c4);

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
