#include "Cylinder.h"
#include <cmath>

Cylinder::Cylinder(Ray director, float radius) : m_director(director), m_radius(radius) {
}

bool Cylinder::Intersects(Ray r, float begin, float end, float* where) const {
	Vector3 v = r.origin - m_director.origin;
	float a = 1 - (r.direction * m_director.direction)*(r.direction * m_director.direction);
	float b = 2*(v * r.direction - (v * m_director.direction) * (r.direction * m_director.direction) );
	float c = - (v * m_director.direction) * (v * m_director.direction) + (v * v) - m_radius * m_radius;

	if(b*b - 4*a*c < 0)
		return false;

	*where = (-b - sqrt(b*b - 4*a*c))/(2*a);
	if(begin <= *where && *where <= end) return true;

	*where = (-b + sqrt(b*b - 4*a*c))/(2*a);
	if(begin <= *where && *where <= end) return true;

	return false;
}

Vector3 Cylinder::Normal(Vector3 at) const {
	Vector3 ret = at - m_director.origin;
	ret = ret - m_director.direction * (ret * m_director.direction);

	ret.Normalize();
	return ret;
}
