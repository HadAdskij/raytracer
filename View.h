#ifndef _VIEW_H_
#define _VIEW_H_

#include <vector>
#include <thread>
#include "Surface.h"
#include "Color.h"
#include "Light.h"

class View {
	private:
		int numThreads = 1;
		Vector3 m_up, m_right;
		std::vector<Surface*> m_scene;
		std::vector<Light*> m_lights;
		int m_width, m_height; // In pixels
		Ray m_viewDirection;
		Color GetPixelColor(int x, int y);
		Color RayColor(Ray r, int depth = 0);
		bool Hit(Ray r, int *surfaceHit, float *at, bool includeGlass = true);
		std::thread* pixelThread;

	public:
		View(int width, int height, Ray viewDirection) : m_width(width), m_height(height), m_viewDirection (viewDirection) {
			Vector3 up = Vector3(0,1,0);
			m_right = viewDirection.direction.Cross(up);
			m_right.Normalize();
			m_up = m_right.Cross(viewDirection.direction);
			pixelThread = new std::thread[numThreads];
		}
		void SetViewDirection(Ray view, Vector3 up);
		void UpdatePixelParallel(int t, Color* pixels);
		void AddSurface(Surface* surface) { m_scene.push_back(surface); }
		void AddLight(Light* light) { m_lights.push_back(light); }
		void DrawScene(Color* outPixels);
};

#endif
