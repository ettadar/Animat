#include "perfimage.hpp"


#include <cmath>



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
        //int x = j ;
		for(int y = height; y < height + SIZEPIXEL; y++)
		{
			if(getPixel(x, y)->r != 0)
				setPixel(_getColor(51, 204, 255), x, y);
		}
}

void Perfimage::drawGoal(int goalPosX, int goalPosY)
{
	for (int g = 0; g <= SIZEPIXEL / 2; ++g)
		setPixel(_getColor(255,0,0), goalPosX + (SIZEPIXEL / 4) + g, goalPosY +  (SIZEPIXEL / 4) + g);
	for (int g = 0; g <= SIZEPIXEL / 2; ++g)
		setPixel(_getColor(255,0,0), goalPosX + (SIZEPIXEL / 4) + g, goalPosY + 3 * (SIZEPIXEL / 4) - g);
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
			if(getPixel(cyl->x + i, cyl->y + j)->r != 0 && cyl->x + i < m_width && cyl->x + i >= 0 && 
				cyl->y + j < m_height && cyl->y + j >= 0 )
			{
				setPixel(c, cyl->x + i, cyl->y + j);			
			}
		}
	}
	std::cout <<"x "<<cyl->x <<" y "<<cyl->y <<	std::endl;
}

void Perfimage::chooseArrow(short width, short height, float moveX, float moveY, float newSize)
{
	if(moveX == 0)
      {
        if (moveY == 0)
        {
        }
        else if (moveY > 0)
        {
          drawArrow(width, height, 0, newSize);
        }
        else if (moveY < 0)
        {
          drawArrow(width, height, 4, newSize);
        }
      }
      else if (moveY == 0)
      {
        if (moveX > 0)
        {
          drawArrow(width, height, 6, newSize);
        }
        else
        {
          drawArrow(width, height, 2, newSize);
        }
      }
      else if (fabs(moveY / moveX) > 2.42)
      {
        if (moveY > 0)
        {
          drawArrow(width, height, 0, newSize);
        }
        else
        {
          drawArrow(width, height, 4, newSize);
        }
      }
      else if (fabs(moveY / moveX) > 0.41)
      {
        if (moveY > 0 && moveX > 0)
        {
          drawArrow(width, height, 7, newSize);
        }
        else if (moveY > 0 && moveX < 0)
        {
          drawArrow(width, height, 1, newSize);
        }
        else if (moveY < 0 && moveX > 0)
        {
          drawArrow(width, height, 5, newSize);
        }
        else if (moveY < 0 && moveX < 0)
        {
          drawArrow(width, height, 3, newSize);
        }
      }
      else
      {
        if(moveX < 0)
        {
          drawArrow(width, height, 2, newSize);
        }
        else if (moveX > 0)
        {
          drawArrow(width, height, 6, newSize);
        }
      }
}

void Perfimage::drawArrow(short positionX, short positionY, int direction, int size)
{
	//direction : 0 south, 1 south-weast, 2 weast, 3 north-west, 4 north, 5 north-east, 6 east, 7 south-east 
  //size = 10;
	Colour c = _getColor(0,0,0);
	switch (direction)
	{
		case 0 :
		{
			for (int i = 0; i < size; ++i)
			{
				setPixel(c, positionX + (SIZEPIXEL / 2), positionY + i + (SIZEPIXEL / 2)); 
			}
			for (int i = 0; i < SIZE_ARROW; ++i)
			{
				setPixel(c, positionX + i + (SIZEPIXEL / 2), positionY + size - i + (SIZEPIXEL / 2));
				setPixel(c, positionX - i + (SIZEPIXEL / 2), positionY + size - i + (SIZEPIXEL / 2));
			}
			break;
		}
		case 1 :
		{
			for (int i = 0; i < size; ++i)
			{
				setPixel(c, positionX - i + (SIZEPIXEL / 2), positionY + i + (SIZEPIXEL / 2)); 
			}
			for (int i = 0; i < SIZE_ARROW; ++i)
			{
				setPixel(c, positionX - size + i + (SIZEPIXEL / 2), positionY + size + (SIZEPIXEL / 2));
				setPixel(c, positionX - size + (SIZEPIXEL / 2), positionY + size - i + (SIZEPIXEL / 2));
			}
			break;
		}
		case 2 :
		{
			for (int i = 0; i < size; ++i)
			{
				setPixel(c, positionX - i + (SIZEPIXEL / 2), positionY + (SIZEPIXEL / 2)); 
			}
			for (int i = 0; i < SIZE_ARROW; ++i)
			{
				setPixel(c, positionX - size + i + (SIZEPIXEL / 2), positionY + (SIZEPIXEL / 2) - i);
				setPixel(c, positionX - size + i + (SIZEPIXEL / 2), positionY + (SIZEPIXEL / 2) + i);
			}
			break;
		}
		case 3 :
		{
			for (int i = 0; i < size; ++i)
			{
				setPixel(c, positionX - i + (SIZEPIXEL / 2), positionY - i + (SIZEPIXEL / 2)); 
			}
			for (int i = 0; i < SIZE_ARROW; ++i)
			{
				setPixel(c, positionX - size + i + (SIZEPIXEL / 2), positionY - size + (SIZEPIXEL / 2));
				setPixel(c, positionX - size + (SIZEPIXEL / 2), positionY - size + i + (SIZEPIXEL / 2));
			}
			break;
		}
		case 4 :
		{
			for (int i = 0; i < size; ++i)
			{
				setPixel(c, positionX + (SIZEPIXEL / 2), positionY - i + (SIZEPIXEL / 2)); 
			}
			for (int i = 0; i < SIZE_ARROW; ++i)
			{
				setPixel(c, positionX + (SIZEPIXEL / 2) + i, positionY - size + i + (SIZEPIXEL / 2));
				setPixel(c, positionX + (SIZEPIXEL / 2) - i, positionY - size + i + (SIZEPIXEL / 2));
			}
			break;
		}

		case 5 :
		{
			for (int i = 0; i < size; ++i)
			{
				setPixel(c, positionX + i + (SIZEPIXEL / 2), positionY - i + (SIZEPIXEL / 2)); 
			}
			for (int i = 0; i < SIZE_ARROW; ++i)
			{
				setPixel(c, positionX + size - i + (SIZEPIXEL / 2), positionY - size + (SIZEPIXEL / 2));
				setPixel(c, positionX + size + (SIZEPIXEL / 2), positionY - size + i + (SIZEPIXEL / 2));
			}
			break;
		}
		case 6 :
		{
			for (int i = 0; i < size; ++i)
			{
				setPixel(c, positionX + i + (SIZEPIXEL / 2), positionY + (SIZEPIXEL / 2)); 
			}
			for (int i = 0; i < SIZE_ARROW; ++i)
			{
				setPixel(c, positionX + size - i + (SIZEPIXEL / 2), positionY + (SIZEPIXEL / 2) - i);
				setPixel(c, positionX + size - i + (SIZEPIXEL / 2), positionY + (SIZEPIXEL / 2) + i);
			}
			break;
		}
		case 7 :
		{
			for (int i = 0; i < size; ++i)
			{
				setPixel(c, positionX + i + (SIZEPIXEL / 2), positionY + i + (SIZEPIXEL / 2));  
			}
			for (int i = 0; i < SIZE_ARROW; ++i)
			{
				setPixel(c, positionX + size - i + (SIZEPIXEL / 2), positionY + size + (SIZEPIXEL / 2));
				setPixel(c, positionX + size + (SIZEPIXEL / 2), positionY + size - i + (SIZEPIXEL / 2));
			}
			break;
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