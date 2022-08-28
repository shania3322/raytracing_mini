#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "test.h"
#include "hittable.h"
#include "shape.h"

//#define ENABLE_TEST

#include <iostream>


Color ray_color(Ray &r, HittableList &obj_list) {
	Intersection rec = Intersection();
	bool if_hit = obj_list.hit(r,0.0f,999999.0f,rec);

	if (if_hit) {
		return 0.5*(unit_vector(rec.normal)+Vec3(1.0f,1.0f,1.0f));
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

	// Camera
	const float focal_length = 1.0f;
	const float viewport_h = 1.0f;
	const float viewport_w = viewport_h * aspect_ratio;
	const Vec3 origin = Vec3(0.0f, 0.0f, 0.0f);
	const Vec3 move_x = Vec3(viewport_w, 0.0f, 0.0f);
	const Vec3 move_y = Vec3(0.0f, viewport_h, 0.0f);
	const Vec3 move_z = Vec3(0.0f, 0.0f, focal_length);
	const Vec3 lower_left_corner = origin-0.5f*move_y-0.5f*move_x-move_z;

	//Sphere
	const Vec3 circle_center= lower_left_corner + Vec3(0.5f,0.4f,-2.0f);
	float circle_radius = 0.5f;
	std::cerr<<"circle_center "<<circle_center<<"\tradius "<<circle_radius<<'\n';

	// Render
	std::cout<<"P3\n"<<img_width<<" "<<img_height<<"\n255\n";

	HittableList obj_list;
	//Sphere c = Sphere(circle_center, circle_radius);
	//Sphere c2 = Sphere(circle_center-Vec3(0.2f,0.2f,0.1f), 0.1f);
	Sphere c3 = Sphere(Vec3(0.0f,-100.5f,-1.0f), 100.0f);
	Sphere c4 = Sphere(Vec3(0.0f,0.0f,-1.0f), 0.5f);
	//obj_list.add(&c);
	//obj_list.add(&c2);
	obj_list.add(&c3);
	obj_list.add(&c4);

	for (int i=img_height-1; i>=0; --i){
		std::cerr<<"\rScanlines remaining:"<<i<<std::flush;
		for (int j=0; j<=img_width-1; ++j){
			float x = float(j)/float(img_width-1);
			float y = float(i)/float(img_height-1);
			Vec3 direction = lower_left_corner+x*move_x+y*move_y-origin;
			Ray r = Ray(origin, direction);

			Color color = ray_color(r,obj_list);
			write_color(std::cout,color);
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
	myTest.test_shape();
}
#endif
