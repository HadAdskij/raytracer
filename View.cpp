#include <stdio.h>
#include <algorithm>
#include <cmath>
#include "View.h"

void View::DrawScene(Color* pixels) {
	for(int t = 0; t < 8; t++)
		pixelThread[t] = std::thread(&View::UpdatePixelParallel,this,t,pixels);
	for(int t = 0; t < 8; t++)
		pixelThread[t].join();
}

void View::UpdatePixelParallel(int t, Color* pixels) {
	int delta = m_height/8;
	for(int i = t * delta; i < (t+1) * delta && i < m_height; i++)
		for(int j = 0; j < m_width; j++)
			pixels[i*m_width + j] = GetPixelColor(i, j);
}

Color View::GetPixelColor(int x, int y) {
	float u = (-m_height + 2*x + 1.0f)/(2*m_height);
	float v = (-m_width*m_width + m_width* (2*y + 1.0f) )/(2*m_width*m_height);

	Color ret = Color(0,0,0);

	// Calculate hits
	
	bool hit = false;
	int surfaceHit = 0;
	float at = 1.0f/0.0f;
	Ray ray(m_viewDirection.origin, m_viewDirection.direction + m_right*v + m_up*u);
	for(int i = 0; i < m_scene.size(); i++) {
		float where;
		if(m_scene[i]->Intersects(ray, ray.direction.Norm(), at, &where)) {
			hit = true;
			surfaceHit = i;
			at = where;
		}
	}

	// Calculate lights
	
	if(hit) {
		// Ambient light
		ret = m_scene[surfaceHit]->GetDiffuseColor() * 0.1;

		for(int i = 0; i < m_lights.size(); i++) {
			Vector3 surfacePoint = ray.origin + ray.direction * at;
			Vector3 lightDir = m_lights[i]->position - surfacePoint;
			Vector3 viewDir = m_viewDirection.origin - surfacePoint;
			Vector3 normal = m_scene[surfaceHit]->Normal(surfacePoint);
			lightDir.Normalize();
			viewDir.Normalize();

			Vector3 h = lightDir + viewDir;
			h.Normalize();

			bool ocluded = false;

			// Shadow
			for(int j = 0; j < m_scene.size() && !ocluded; j++) {
				float where;
				if(j == surfaceHit) continue;
				if(m_scene[j]->Intersects(Ray(surfacePoint, lightDir), 0, (m_lights[i]->position - surfacePoint).Norm(), &where))
					ocluded = true;
			}
			if(ocluded) continue;

			float nl = normal * lightDir;
			float nh = normal * h;

			//nl = floor(nl * 4)/4;
			//nh = floor(nh * 4)/4;

			ret = ret + m_scene[surfaceHit]->GetDiffuseColor()*m_lights[i]->intensity*std::max(0.0f, nl) + Color(0.4,0.4,0.4) * m_lights[i]->intensity * pow(std::max(0.0f, nh), 1000);
		}
	}

	return ret;
}
