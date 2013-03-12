#ifndef LANDSCAPE_HPP
# define LANDSCAPE_HPP

#include <vector>

struct LandscapeElem
{
	LandscapeElem(bool gap, float center, float size, float hue=0,
		float sat=0, float lum=0):
		gap(gap),
		center(center),
		size(size),
		hue(hue),
		sat(sat),
		lum(lum) {};
	bool gap;
	float center;
	float size;
	float hue;
	float sat;
	float lum;
};

typedef std::vector<LandscapeElem*> Landscape;

#endif // !LANDSCAPE_HPP
