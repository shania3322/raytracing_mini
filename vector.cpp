#include "vec3.h"
#include <cassert>

int main(){
	Vec3 v1 = Vec3(2.0f, 1.0f, 1.0f);
	Vec3 v2 = Vec3(1.0f, 3.0f, 1.0f);

	Vec3 r1 = v1+v2;
	Vec3 r2 = v1 * 2.0f;
	float r3 = dot(v1,v2);
	Vec3 r4 = v1-v2;
	Vec3 r5 = v2/2.0f;
	Vec3 r6 = -v2;
	Vec3 r7 = cross(v1,v2);
	Vec3 r8 = unit_vector(v1);

	// Debug only
	//assert(r1 == Vec3(3.0f, 4.0f, 2.0f));
	//assert(r2 == Vec3(4.0f, 2.0f, 2.0f));
	//assert(r3 == 6.0f);
	//assert(r4 == Vec3(1.0f, -2.0f, 0.0f));
	//assert(r5 == Vec3(0.5f, 1.5f, 0.5f));
	//assert(r6 == Vec3(-1.0f, -3.0f, -1.0f));
	//assert(r7 == Vec3(-2.0f, -1.0f, 5.0f));

	std::cout<<"Add:"<<r1<<"\n"
			<<"multiply a number:"<<r2<<"\n"
			<<"multiply a vector:"<<r3<<"\n"
			<<"Substract a vector:"<<r4<<"\n"
			<<"divided by a number:"<<r5<<"\n"
			<<"negate:"<<r6<<"\n"
			<<"cross product of two vectors:"<<r7<<"\n"
			<<"length of a vector:"<<v1.length()<<"\n"
			<<"Unit vector:"<<r8<<"\n"
			<<std::endl;
}
