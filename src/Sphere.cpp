#include "Sphere.h"
#include <stdio.h>
#include <cmath>

Sphere::Sphere(Vector3 center, float radius) : m_center(center), m_radius(radius) {
}

bool Sphere::Intersects(Ray r, float begin, float end, float* where) const {
	//printf("Tentando acertar esfera de raio %f em (%f, %f, %f) contra raio em (%f, %f, %f) e dir (%f,%f,%f)\n",
	//		m_radius, m_center.x, m_center.y, m_center.z, r.origin.x, r.origin.y, r.origin.z, r.direction.x, r.direction.y, r.direction.z);
	float a = r.direction.SquareNorm();
	float b = (r.origin - m_center) * r.direction * 2;
	float c = (r.origin - m_center).SquareNorm() - m_radius*m_radius;

	if(b*b - 4*a*c < 0)
		return false;

	*where = (-b - sqrt(b*b - 4*a*c))/(2*a);
	if(begin <= *where && *where <= end) return true;

	*where = (-b + sqrt(b*b - 4*a*c))/(2*a);
	if(begin <= *where && *where <= end) return true;

	return false;
}

Vector3 Sphere::Normal(Vector3 at) const {
	Vector3 ret = at - m_center;

	ret.Normalize();
	return ret;
}
