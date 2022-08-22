#include "vec3.h"
#include "color.h"
#include "ray.h"

//#define ENABLE_TEST

#include <iostream>



bool solve_circle(Vec3 C, float radius, const Ray &p) {
	/* ray: P=A+t*D
	 * Circle: center C, radius r
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
	float t=0.0f;

	Vec3 A = p.origin;
	Vec3 D = p.direction;
	float a = dot(D,D);
	float b = 2.0f*dot(D, (A-C));
	float c = dot((A-C),(A-C)) - radius*radius;

	float discriminant = b*b-4.0f*a*c;
	//if (discriminant == 0.0f) {
	//	t = -1.0f/(2.0f*a)*b;
	//}
	//else if (discriminant > 0.0f) {
	//	t = -b-(1.0f/2.0f*a)*sqrt(discriminant);
	//	// t2 = -b+(1.0f/2.0f*a)*sqrt(discriminant),
	//	// but we only render the closer point, thus t2 is omitted.
	//}
	return (discriminant>0);
}

Color circle_color() {
	return Color(1.0f,0.0f,0.0f);
}

Color ray_color(const Ray &r) {
	Vec3 unit = unit_vector(r.direction-r.origin);
	float t = (unit.y+1.0)*0.5f;
	return (1.0f-t)*Color(1.0f,1.0f,1.0f)+t*Color(0.5,0.7,1.0f);
}
#ifndef ENABLE_TEST
int main() {
	// Image
	const float aspect_ratio = 6.0f/3.0f;
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
	float circle_radius = 1.0f;
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
			bool t = solve_circle(circle_center, circle_radius, r);
			if (t){
				Color color = circle_color();
				write_color(std::cout,color);
			} else {
				Color color = ray_color(r);
				write_color(std::cout,color);
			}

			//float r = float(j)/float(img_width-1);
			//float g = float(i)/float(img_height-1);
			//float b = 0.25;

			//Color pixel_color = Color(r,g,b);
			//write_color(std::cout,pixel_color);

			//int ir = int(255.0f*r);
			//int ig = int(255.0f*g);
			//int ib = int(255.0f*b);

			//std::cout<<ir<<"\t"<<ig<<"\t"<<ib<<"\n";
			//std::cout<<color<<"\n";

		}
	}
	std::cerr<<"\nDone.\n";
	return 0;
}
#else
int main()
{
	Test myTest = Test();
	myTest.runTest();
}
#endif
