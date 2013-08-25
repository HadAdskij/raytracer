#ifndef _LIGHT_H_
#define _LIGHT_H

struct Light {
	Vector3 position;
	float intensity;
	Light() {}
	Light(Vector3 position, float intensity) : position(position), intensity(intensity) {}
};

#endif
