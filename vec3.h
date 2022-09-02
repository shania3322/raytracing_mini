#pragma once

#include <iostream>
#include <cmath>
#include "util.h"

class Vec3
{
	public:
		float x;
		float y;
		float z;

		Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
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

Vec3 operator*(Vec3 v1, Vec3 v2) {
	return Vec3(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
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

// Generate a random Vec3 point v such that v.x, v.y and v.z are in range [-1,1]
Vec3 random_vec3() {
	Vec3 v;
	v.x = random_float();
	v.y = random_float();
	v.z = random_float();
	return v;
}

Vec3 random_vec3(float min, float max) {
	Vec3 v;
	v.x = random_float(min,max);
	v.y = random_float(min,max);
	v.z = random_float(min,max);
	return v;
}

Vec3 random_in_unit_sphere() {
	// rejection sampling
	while(true) {
		Vec3 next_point = random_vec3(-1.0f,1.0f);
		if ( dot(next_point,next_point)<1 ) {
			return next_point;
		}
	}
}

bool near_zero(Vec3 v) {
	const float e = 1e-8;
	return (v.length()<e);
}

Vec3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

Vec3 reflected(Vec3 r, Vec3 n) {
	return 2*dot(-r,n)*n + r;
}

float angle_cos(Vec3 v1, Vec3 v2) {
	return dot(v1, v2)/(v1.length()*v2.length());
}

//Type alias
//using Point3 = Vec3;
using Color = Vec3;

std::ostream& operator<<(std::ostream& os, const Vec3 v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}


