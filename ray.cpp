#include "ray.h"
#include <iostream>

int main(){
	Vec3 origin = Vec3(1.0f,1.0f,1.0f);
	Vec3 direction = Vec3(0.0f, 2.0f, 0.0f);
	Ray r2 = Ray(origin, direction);
	Vec3 ray = r2.at(3.0f);

	std::cout<<"Ray:" <<r2.origin<<'-'<<r2.direction<<' '
		<<"Ray at t=3.0:"<<ray<<'\n';
}
