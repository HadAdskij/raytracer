#include <stdio.h>
#include <algorithm>
#include <cmath>
#include "View.h"

void View::DrawScene(Color* pixels) {
	for(int t = 0; t < numThreads; t++)
		pixelThread[t] = std::thread(&View::UpdatePixelParallel,this,t,pixels);
	for(int t = 0; t < numThreads; t++)
		pixelThread[t].join();
}

void View::SetViewDirection(Ray view, Vector3 up) {
	up.Normalize();
	m_viewDirection = view;
	m_right = view.direction.Cross(up);
	m_up = m_right.Cross(view.direction);
}

void View::UpdatePixelParallel(int t, Color* pixels) {
	int delta = m_height/numThreads;
	for(int i = t * delta; i < (t+1) * delta && i < m_height; i++)
		for(int j = 0; j < m_width; j++)
			pixels[i*m_width + j] = GetPixelColor(i, j);
}

Color View::GetPixelColor(int x, int y) {
	float u = (-m_height + 2*x + 1.0f)/(2*m_height);
	float v = (-m_width*m_width + m_width* (2*y + 1.0f) )/(2*m_width*m_height);

	Ray ray(m_viewDirection.origin + m_viewDirection.direction + m_right*v + m_up*u, m_viewDirection.direction + m_right*v + m_up*u);
	return RayColor(ray);
}

bool View::Hit(Ray ray, int *outIndex, float *at, bool includeGlass) {
	bool hit = false;
	*outIndex = 0;
	for(int i = 0; i < m_scene.size(); i++) {
		float where;
		if(!includeGlass && m_scene[i]->IsGlass()) continue;
		if(m_scene[i]->Intersects(ray, 0.001, *at, &where)) {
			hit = true;
			*outIndex = i;
			*at = where;
		}
	}
	return hit;
}

Color View::RayColor(Ray ray, int depth) {

	if(depth == 2) return Color(0,0,0);

	// Calculate lights
	
	int surfaceHit;
	float at = 1.0f/0.0f;;
	if(Hit(ray, &surfaceHit, &at)) {
		Color ret = Color(0,0,0);
		Surface* surface = m_scene[surfaceHit];
		if(surface->IsGlass())
			return RayColor(surface->GetRefractedRay(ray, at),  depth);

		for(int i = 0; i < m_lights.size(); i++) {
			Vector3 surfacePoint = ray.origin + ray.direction * at;
			Vector3 lightDir = m_lights[i]->position - surfacePoint;
			Vector3 viewDir = m_viewDirection.origin - surfacePoint;
			Vector3 normal = surface->Normal(surfacePoint);
			lightDir.Normalize();
			viewDir.Normalize();

			Vector3 h = lightDir + viewDir;
			h.Normalize();

			// Shadows
			int sHit;
			float at = lightDir.Norm();

			float nl = normal * lightDir;
			float nh = normal * h;

			if(!Hit(Ray(surfacePoint, lightDir), &sHit, &at, false))
				ret = ret + surface->GetDiffuseColor()*m_lights[i]->intensity*std::max(0.0f, nl) + Color(0.4,0.4,0.4) * m_lights[i]->intensity * pow(std::max(0.0f, nh), 1000);
			
			float reflection = surface->GetReflectionIndex();
			if(reflection > 0) {
				ret = ret + RayColor(Ray(surfacePoint, normal * (viewDir * normal) * 2 - viewDir), depth+1) * reflection;
			}
		}
		return ret;
	}

	// Ambient light
	return Color(0,0,0);
	//return Color(0.55, 0.75, 0.84);
}
