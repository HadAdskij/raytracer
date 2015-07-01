#ifndef _VIEW_H_
#define _VIEW_H_

#include <vector>
#include <thread>
#include <memory>
#include "Surface.h"
#include "Color.h"
#include "Light.h"

class View {
	private:
		int numThreads;
		Vector3 m_up, m_right;
		std::vector<std::shared_ptr<Light> > m_lights;
		std::vector<std::shared_ptr<Surface> > m_scene;
		int m_width, m_height; // In pixels
		Ray m_viewDirection;
		Color GetPixelColor(int x, int y);
		Color RayColor(Ray r, int depth = 0);
		bool Hit(Ray r, int *surfaceHit, float *at, bool includeGlass = true);
		std::thread* pixelThread;

	public:
		View() {}
		View(int width, int height, Ray viewDirection) : numThreads(1), m_width(width), m_height(height), m_viewDirection (viewDirection) {
			Vector3 up = Vector3(0,1,0);
			m_right = viewDirection.direction.Cross(up);
			m_right.Normalize();
			m_up = m_right.Cross(viewDirection.direction);
			pixelThread = new std::thread[numThreads];
		}
		void SetViewDirection(Ray view, Vector3 up);
		void UpdatePixelParallel(int t, Color* pixels);
		void AddSurface(std::shared_ptr<Surface> surface) { m_scene.push_back(surface); }
		void AddLight(std::shared_ptr<Light> light) { m_lights.push_back(light); }
		void DrawScene(Color* outPixels);
};

#endif
