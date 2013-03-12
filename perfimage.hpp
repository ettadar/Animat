#ifndef PERFIMAGE_HPP
# define PERFIMAGE_HPP

#include "Image.h"
#include "type.hpp"
#include "cylinder.hpp"


class Perfimage : public TGAImage
{
public :
	Perfimage(short width, short height);
	~Perfimage();
	void colorPixel(short witdth, short height);
	void drawGoal(int goalPosX, int goalPosY);
	void drawLandmark(Cylinder* cyl);
	void drawArrow(short witdth, short height, float moveX, float moveY);
	void bresenham(int x1, int y1, int x2, int y2);

private :
	Colour _getColor(int r, int g, int b, int a=255);
};



#endif // !PERFIMAGE_HPP