#pragma once

#include <cstdlib>

#define PI 3.14159265358979f

float random_float() {
	//return value in range [0,1)
	return float(rand())/float(RAND_MAX);
}

float random_float(float min, float max) {
	float num = random_float();
	return min+(max-min)*num;
}

float clamp (float x, float min, float max) {
	if (x>max) {
		x=max;
	}
	if (x<min) {
		x=min;
	}
	return x;
}

float degree2rad(float degree) {
	return (degree*PI)/180.0f;
}
