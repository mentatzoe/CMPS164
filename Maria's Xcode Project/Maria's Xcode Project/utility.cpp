#include "utility.h"

float dot(float *a, float *b) {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float angle(float *a, float *b) {
	float mag_a = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	float mag_b = sqrt(b[0] * b[0] + b[1] * b[1] + b[2] * b[2]);
	return acosf(dot(a, b) / (mag_a * mag_b));
}

std::vector<float> cross(float *a, float *b){
	std::vector<float> crossResult;
	crossResult[0] = (a[1] * b[2]) - (a[2] * b[1]);
	crossResult[1] = (a[0] * b[2]) - (a[2] * b[0]);
	crossResult[2] = (a[0] * b[1]) - (a[1] * b[0]);
	return crossResult;
}