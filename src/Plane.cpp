#include "Plane.h"

Plane::Plane(Vector3 point, Vector3 normal) : m_point(point), m_normal(normal) {
	m_normal.Normalize();
}

bool Plane::Intersects(Ray r, float begin, float end, float *where) const {
	float vn = -(r.direction * m_normal);

	if(vn == 0) {
		*where = begin;
		return (r.origin - m_point) * m_normal == 0;
	}

	*where = ((r.origin - m_point) * m_normal)/vn;
	return (begin <= *where) && (*where <= end);
}

Vector3 Plane::Normal(Vector3) const {
	return m_normal;
}
