#pragma once

#include "vec3.h"
#include "shape.h"

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
	Circle c2 = Circle(Vec3(1.0f,0.0f,0.0f), 0.1f);
	std::cout<<"center-"<<c2.center<<' '<<"radius-"<<c2.radius<<'\n';
	Plane p = Plane();
}
