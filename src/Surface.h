#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "Ray.h"
#include "Color.h"
#include <cmath>
#include <cstdio>
#include <limits>

class Surface
{
	private:
		float m_reflectionIndex;
		Color m_diffuseColor;
		Color m_specularColor;
		bool m_isGlass;
		float m_refractionIndex;

	public:
		Surface() : m_reflectionIndex(0), m_refractionIndex(1), m_isGlass(false) {}

		virtual bool Intersects(Ray r, float begin, float end, float* where) const = 0;
		virtual Vector3 Normal(Vector3 at) const = 0;

		void SetDiffuseColor(Color color) { m_diffuseColor = color; }
		Color GetDiffuseColor() const { return m_diffuseColor; }
		void SetSpecularColor(Color color) { m_specularColor = color; }

		void SetReflectionIndex(float r) { m_reflectionIndex = r; }
		float GetReflectionIndex() const { return m_reflectionIndex; }

		bool IsGlass() const { return m_isGlass; }
		void SetGlass(bool glass) { m_isGlass = glass; }
		void SetRefractionIndex(float index) { m_refractionIndex = index; }
		
		// Refracts an incoming ray l about n
		Vector3 Refract(Vector3 l, Vector3 n, float n1, float n2) const {
			float cosTheta1 = n*l*(-1);
			float cosTheta2 = sqrt(1 - (n1/n2) * (n1/n2) * (1 - cosTheta1 * cosTheta1));

			return l * (n1/n2) + n * (n1/n2 * cosTheta1 - cosTheta2);
		}

		Ray GetRefractedRay(Ray r, float at) const {
			Vector3 p = r.origin + r.direction * at;
			Vector3 firstRefract = Refract(r.direction, Normal(p), 1, m_refractionIndex);

			float where;
			if(!Intersects(Ray(p, firstRefract), 0.01f, std::numeric_limits<float>::infinity(), &where))
				return Ray(p, firstRefract);

			Vector3 p2 = p + firstRefract * where; 
			return Ray(p2, Refract(firstRefract, Normal(p2)*(-1), m_refractionIndex, 1));
		}
};

#endif
