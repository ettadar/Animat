#ifndef LANDSCAPE_HPP
# define LANDSCAPE_HPP

#include <vector>
#include <iostream>

struct LandscapeElem
{
	LandscapeElem(bool gap, float angle, float size, float hue=0,
		float sat=0, float lum=0):
		gap(gap),
		angle(angle),
		size(size),
		hue(hue),
		sat(sat),
		lum(lum) {};
	bool gap;
	float angle;
	float size;
	float hue;
	float sat;
	float lum;
};

typedef std::vector<LandscapeElem*> Landscape;

//friend ostream& operator<< (ostream&, LandscapeElem elem);



#endif // !LANDSCAPE_HPP
