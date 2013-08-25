#ifndef _RAY_H_
#define _RAY_H_

#include "Vector3.h"

struct Ray {
	Vector3 origin, direction;

	Ray(){}
	Ray(Vector3 origin, Vector3 direction) : origin(origin), direction(direction) {
		this->direction.Normalize();
	}
};

#endif
