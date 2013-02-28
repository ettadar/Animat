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
	void chooseArrow(short witdth, short height, float moveX, float moveY, float newSize);
	void drawArrow(short positionX, short positionY, int direction, int size);

private :
	Colour _getColor(int r, int g, int b, int a=255);
};



#endif // !PERFIMAGE_HPP