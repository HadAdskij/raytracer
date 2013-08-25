#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "Ray.h"
#include "Color.h"

class Surface
{
	private:
		Color m_diffuseColor;
		Color m_specularColor;

	public:
		virtual bool Intersects(Ray r, float begin, float end, float* where) = 0;
		virtual Vector3 Normal(Vector3 at) = 0;
		void SetDiffuseColor(Color color) { m_diffuseColor = color; }
		Color GetDiffuseColor() { return m_diffuseColor; }
		void SetSpecularColor(Color color) { m_specularColor = color; }
};

#endif
