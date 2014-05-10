#include "utility.h"
#include <iostream>

float dot(Vector3f a, Vector3f b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

float angle(Vector3f a, Vector3f b) {
	float mag_a = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	float mag_b = sqrt(b.x * b.x + b.y * b.y + b.z * b.z);
	return acosf(dot(a, b) / (mag_a * mag_b));
}

float magnitude(Vector3f a){
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
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

	for (int i = 0; i < vertList.size(); i++){
		Vector3f curVert = vertList[i];
		Vector3f nextVert = vertList[(i+1) % vertList.size()];

		normal.x = normal.x + ((curVert.y - nextVert.y) * (curVert.z + nextVert.z));
		normal.y = normal.y + ((curVert.z - nextVert.z) * (curVert.x + nextVert.x));
		normal.z = normal.z + ((curVert.x - nextVert.x) * (curVert.y + nextVert.y));
	}

	return normalize(normal);
}