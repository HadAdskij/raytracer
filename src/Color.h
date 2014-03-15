#ifndef _COLOR_H_
#define _COLOR_H_

struct Color {
	float r, g, b;

	Color() {};
	Color(float r, float g, float b) : r(r), g(g), b(b) {}

	Color operator * (const float t) {
		return Color(t*r, t*g, t*b);
	}

	Color operator + (const Color &c) {
		return Color(r + c.r, g + c.g, b + c.b);
	}

	Color operator - (const Color &c) {
		return Color(r - c.r, g - c.g, b - c.b);
	}
};

#endif
