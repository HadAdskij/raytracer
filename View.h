#ifndef _VIEW_H_
#define _VIEW_H_

#include <vector>
#include <thread>
#include "Surface.h"
#include "Color.h"
#include "Light.h"

class View {
	private:
		Vector3 m_up, m_right;
		std::vector<Surface*> m_scene;
		std::vector<Light*> m_lights;
		int m_width, m_height; // In pixels
		Ray m_viewDirection;
		Color GetPixelColor(int x, int y);
		std::thread pixelThread[8];

	public:
		View(int width, int height, Ray viewDirection) : m_width(width), m_height(height), m_viewDirection (viewDirection) {
			Vector3 up = Vector3(0,1,0);
			m_right = viewDirection.direction.Cross(up);
			m_right.Normalize();
			m_up = m_right.Cross(viewDirection.direction);
		}
		void UpdatePixelParallel(int t, Color* pixels);
		void AddSurface(Surface* surface) { m_scene.push_back(surface); }
		void AddLight(Light* light) { m_lights.push_back(light); }
		void DrawScene(Color* outPixels);
};

#endif
