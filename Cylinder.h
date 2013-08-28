#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include "Surface.h"

class Cylinder : public Surface {
	public:
		Cylinder(Ray director, float radius);
		virtual bool Intersects(Ray r, float begin, float end, float* where);
		virtual Vector3 Normal(Vector3 at);

	private:
		Ray m_director;
		float m_radius;
};

#endif
