#pragma once

#include <iostream>
#include <cmath>

class Vec3
{
	public:
		float x;
		float y;
		float z;

		Vec3() : x(0.0), y(0.0), z(0.0) {}
		Vec3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

		Vec3 operator+(Vec3 v) const {
			return Vec3(x+v.x, y+v.y, z+v.z);
		}

		Vec3 operator-(Vec3 v) const {
			return Vec3(x-v.x, y-v.y, z-v.z);
		}

		float length() const {
			return sqrt(x*x+y*y+z*z);
		}

		bool operator==(Vec3 v) const {
			return(x == v.x && y == v.y && z == v.z);
		}
};

Vec3 operator*(float n, Vec3 v) {
	return Vec3(n*v.x, n*v.y, n*v.z);
}

Vec3 operator*(Vec3 v, float n) {
	return n * v;
}

Vec3 operator/(Vec3 v, float n) {
	return 1.0f/n * v;
}

Vec3 operator-(Vec3 v) {
	return Vec3(-v.x,-v.y,-v.z);
}

float dot(Vec3 v0, Vec3 v1) {
	return (v0.x*v1.x+v0.y*v1.y+v0.z*v1.z);
}

Vec3 cross(Vec3 v0, Vec3 v1){
	//Right-hand rule
	/*
	a x b =
	|i			j		k   |
	|v0.x		v0.y	v0.z|
	|v1.x		v1.y	v1.z|
	*/
	float i_ = v0.y*v1.z-v0.z*v1.y;
	float j_ = v0.z*v1.x-v0.x*v1.z;
	float k_ = v0.x*v1.y-v0.y*v1.x;
	return Vec3(i_,j_,k_);
}

Vec3 unit_vector(Vec3 v) {
	return v/v.length();
}

//Type alias
//using Point3 = Vec3;
using Color = Vec3;

std::ostream& operator<<(std::ostream& os, const Vec3 v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}


