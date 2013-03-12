#include "perfimage.hpp"

#include <cmath>

#include "../const.hpp"

Perfimage::Perfimage(short width, short height) : 
	TGAImage(width, height)
{	
}

Perfimage::~Perfimage()
{
}

void Perfimage::colorPixel(short width, short height)
{
	//Loop through image and set all pixels to red
	for(int x = width; x < width + SIZEPIXEL; x++)
		for(int y = height; y < height + SIZEPIXEL; y++)
		{
			if(getPixel(x, y)->r != 0)
				setPixel(_getColor(51, 204, 255), x, y);
		}
}

void Perfimage::drawGoal(int goalPosX, int goalPosY)
{
	for (int g = -SIZEPIXEL / 4; g <= SIZEPIXEL / 4; ++g)
	{
		setPixel(_getColor(255,0,0), goalPosX + g, goalPosY + g);
		setPixel(_getColor(255,0,0), goalPosX + g, goalPosY - g);
	}
}

void Perfimage::drawLandmark(Cylinder* cyl)
{
	Colour c;
	if (cyl->color == 1)
	{
		c = _getColor(255, 0, 0);
	}	
	else if (cyl->color == 2)
	{
		c = _getColor(0,0,255);
	}	
	else if (cyl->color == 3)
	{
		c = _getColor(0,255,0);
	}
	for (int i = -cyl->r; i < cyl->r; ++i)
	{
		for (int j  = -cyl->r; j < cyl->r; ++j)
		{
			if(cyl->x + i < m_width && cyl->x + i >= 0 && 
				cyl->y + j < m_height && cyl->y + j >= 0 &&
				getPixel(cyl->x + i, cyl->y + j)->r != 0 && (pow(i,2) + pow(j,2)) < pow(cyl->r,2))
			{
				setPixel(c, cyl->x + i, cyl->y + j);			
			}
		}
	}
}

void Perfimage::drawArrow(short width, short height, float moveX, float moveY)
{
	if (moveX < 0)
		moveX = -log(-moveX + 1);
	else
		moveX = log(moveX + 1);	
	if (moveY < 0)
		moveY = -log(-moveY + 1);
	else
		moveY = log(moveY + 1);
	if (moveX != 0. || moveY != 0.)
	{
		bresenham(width, height, moveX * SIZE_BARE + width, moveY * SIZE_BARE + height);
		float nMoveX = moveX / sqrt(pow(moveX, 2) + pow(moveY, 2));
		float nMoveY = moveY / sqrt(pow(moveX, 2) + pow(moveY, 2));

		bresenham(moveX * SIZE_BARE + width, moveY * SIZE_BARE + height, (moveX * SIZE_BARE + width) - nMoveY * SIZE_ARROW - nMoveX * SIZE_ARROW, (moveY * SIZE_BARE + height) + nMoveX * SIZE_ARROW - nMoveY * SIZE_ARROW);
		bresenham(moveX * SIZE_BARE + width, moveY * SIZE_BARE + height, (moveX * SIZE_BARE + width) + nMoveY * SIZE_ARROW - nMoveX * SIZE_ARROW, (moveY * SIZE_BARE + height) - nMoveX * SIZE_ARROW - nMoveY * SIZE_ARROW);
	}//fin if move X et move Y = 0
}

void Perfimage::bresenham(int x1, int y1, int x2, int y2)
{
	int delta_x(x2 - x1);
	// if x1 == x2, then it does not matter what we set here
	signed char const ix((delta_x > 0) - (delta_x < 0));
	delta_x = (int)std::abs(delta_x) << 1;

	int delta_y(y2 - y1);
	// if y1 == y2, then it does not matter what we set here
	signed char const iy((delta_y > 0) - (delta_y < 0));
	delta_y = (int)std::abs(delta_y) << 1;

	setPixel(_getColor(0, 0, 0), x1, y1);

	if (delta_x >= delta_y)
	{
		// error may go below zero
		int error(delta_y - (delta_x >> 1));

		while (x1 != x2)
		{
			if ((error >= 0) && (error || (ix > 0)))
			{
				error -= delta_x;
				y1 += iy;
			}
			// else do nothing

			error += delta_y;
			x1 += ix;
			setPixel(_getColor(0, 0, 0), x1, y1);
		}
	}
	else
	{
		// error may go below zero
		int error(delta_x - (delta_y >> 1));

		while (y1 != y2)
		{
			if ((error >= 0) && (error || (iy > 0)))
			{
				error -= delta_y;
				x1 += ix;
			}
			// else do nothing

			error += delta_x;
			y1 += iy;

			setPixel(_getColor(0, 0, 0), x1, y1);
		}
	}
}


Colour Perfimage::_getColor(int r, int g, int b, int a)
{
	Colour c;
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return c;
}