#include "vec3.h"
#include "shape.h"
#include "hittable.h"

#include <iostream>

class Test
{
	public:
		//void runTest();
		void test_shape();

};


//void Test::runTest()
//{
//	assert()
//}

void Test::test_shape() {
	Sphere c1{};
	Sphere c2 = Sphere(Vec3(1.0f,0.0f,0.0f), 0.1f);
	std::cout<<"center-"<<c2.center<<' '<<"radius-"<<c2.radius<<'\n';
	std::cout<<"center-"<<c1.center<<' '<<"radius-"<<c1.radius<<'\n';

	Intersection rec{};
	std::cout<<rec.point<<'\n'<<rec.normal<<'\n'<<rec.t<<'\n'<<rec.frontface<<'\n';
	//Plane p = Plane();
}
