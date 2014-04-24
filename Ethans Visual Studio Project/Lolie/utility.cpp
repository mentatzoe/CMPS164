#include "utility.h"
#include <iostream>

float dot(float *a, float *b) {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float angle(float *a, float *b) {
	float mag_a = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	float mag_b = sqrt(b[0] * b[0] + b[1] * b[1] + b[2] * b[2]);
	return acosf(dot(a, b) / (mag_a * mag_b));
}

Vector3f cross(Vector3f a, Vector3f b) {
	Vector3f result;
	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);
	return result;
}

Vector3f normalize(Vector3f orig) {
	float magnitude = sqrtf((orig.x * orig.x) + (orig.y * orig.y) + (orig.z * orig.z));
	Vector3f result((orig.x / magnitude), (orig.y / magnitude), (orig.z / magnitude));
	return result;
}

Vector3f calcSurfaceNormal(std::vector<Vector3f> vertList) {
	Vector3f normal = { 0, 0, 0 };

	for (int i = 0; i <= vertList.size() - 1; i++) {
		//std::cout << "i = " << i << ", verList.size() = " << vertList.size() << "\n";
		Vector3f curVert = vertList[i];
		Vector3f nextVert = vertList[(i + 1) % vertList.size()];

		normal.x = normal.x + ((curVert.y - nextVert.y) * (curVert.z + nextVert.z));
		normal.y = normal.y + ((curVert.z - nextVert.z) * (curVert.x + nextVert.x));
		normal.z = normal.z + ((curVert.x - nextVert.x) * (curVert.z + nextVert.y));
	}

	return normalize(normal);
}