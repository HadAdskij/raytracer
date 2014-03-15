#ifndef _PLANE_H_
#define _PLANE_H_

#include "Surface.h"

class Plane : public Surface {
	public:
		// Plane defined by a point in it and a normal
		Plane(Vector3 point, Vector3 normal);
		virtual bool Intersects(Ray r, float begin, float end, float* where);
		virtual Vector3 Normal(Vector3 at);

	private:
		Vector3 m_point, m_normal;
};

#endif
