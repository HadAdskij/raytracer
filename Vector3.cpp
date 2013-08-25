#include "Vector3.h"
#include <cmath>

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {
}

Vector3 Vector3::operator + (const Vector3 &v) {
	return Vector3(x+v.x, y+v.y, z+v.z);
}

Vector3 Vector3::operator - (const Vector3 &v) {
	return Vector3(x-v.x, y-v.y, z-v.z);
}

Vector3 Vector3::operator * (const float t) {
	return Vector3(t*x, t*y, t*z);
}

float Vector3::operator * (const Vector3 &v) {
	return x*v.x + y*v.y + z*v.z;
}

bool Vector3::operator == (const Vector3 &v) {
	return x == v.x && y == v.y && z == v.z;
}

Vector3 Vector3::Cross(const Vector3 &v) {
	return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

float Vector3::SquareNorm() {
	return (*this)*(*this);
}

float Vector3::Norm() {
	return sqrt(SquareNorm());
}

void Vector3::Normalize() {
	float norm = Norm();
	x /= norm; y /= norm; z /= norm;
}
