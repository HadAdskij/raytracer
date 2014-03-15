#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Surface.h"

class Sphere : public Surface {
	public:
		Sphere(Vector3 center, float radius);
		virtual bool Intersects(Ray r, float begin, float end, float* where);
		virtual Vector3 Normal(Vector3 at);

	private:
		Vector3 m_center;
		float m_radius;
};

#endif
