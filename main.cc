#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "test.h"
#include "shape.h"
#include "hittable.h"

//#define ENABLE_TEST

#include <iostream>


Color circle_color() {
	return Color(1.0f,0.0f,0.0f);
}

Color ray_color(Ray &r, Circle &c) {
	Intersection rec = Intersection();
	bool if_hit = c.hit(r,0.5f,1.0f, rec);

	if (if_hit) {
		rec.set_normal(r);
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
	const int img_height = int(1.0f / aspect_ratio * float(img_width));

	// Camera
	const float focal_length = 1.0f;
	const float viewport_h = 1.0f;
	const float viewport_w = viewport_h / aspect_ratio;
	const Vec3 origin = Vec3(0.0f, 0.0f, 0.0f);
	const Vec3 move_x = Vec3(viewport_h, 0.0f, 0.0f);
	const Vec3 move_y = Vec3(0.0f, viewport_w, 0.0f);
	const Vec3 move_z = Vec3(0.0f, 0.0f, focal_length);
	const Vec3 lower_left_corner = origin-0.5f*move_y-0.5f*move_x-move_z;

	//Circle
	const Vec3 circle_center= lower_left_corner + Vec3(0.5f,0.4f,-2.0f);
	float circle_radius = 0.5f;
	std::cerr<<"circle_center "<<circle_center<<"\tradius "<<circle_radius<<'\n';

	// Render
	std::cout<<"P3\n"<<img_width<<" "<<img_height<<"\n255\n";

	for (int i=img_height-1; i>=0; --i){
		std::cerr<<"\rScanlines remaining:"<<i<<std::flush;
		for (int j=0; j<=img_width-1; ++j){
			float x = float(j)/float(img_width-1);
			float y = float(i)/float(img_height-1);
			Vec3 direction = lower_left_corner+x*move_x+y*move_y-origin;

			Ray r = Ray(origin, direction);
			Circle c = Circle(circle_center, circle_radius);

			Color color = ray_color(r,c);
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
