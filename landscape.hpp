#ifndef LANDSCAPE_HPP
# define LANDSCAPE_HPP

#include <list>

struct LandscapeElem
{
	LandscapeElem(bool gap, float angle, float hue=0,
		float sat=0, float lum=0):
		gap(gap),
		angle(angle),
		hue(hue),
		sat(sat),
		lum(lum) {};
	bool gap;
	float angle;
	float hue;
	float sat;
	float lum;
};

typedef std::list<LandscapeElem*> Landscape;

#endif // !LANDSCAPE_HPP