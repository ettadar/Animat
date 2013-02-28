#include "dynamicmodelcolor.hpp"

DynamicModelColor::DynamicModelColor(Image* goalViewImg) :
	DynamicModel(goalViewImg)
{
	_goalViewLand = _imageToLandscape(goalViewImg);
}

Landscape* DynamicModelColor::_imageToLandscape(Image* img)
{
	Landscape* land = new Landscape();	

	float begin = 0;
	int currColor = img->at(0);
	int i = 0;
	for (i = 0; i < img->size(); i++)
	{
		if (img->at(i) != currColor)
		{
			if (currColor == RED)
			{
				land->push_back(new LandscapeElem(false, (i + begin - 1 - VIEW_ANGLE) / 2. / 360. * PI,
					(i - begin) / 360. * PI, HUERED, SATRED, VALUERED));
			}
			else if (currColor == BLUE)
			{
				land->push_back(new LandscapeElem(false, (i + begin - 1 - VIEW_ANGLE) / 2. / 360. * PI,
					(i - begin) / 360. * PI, HUEBLUE, SATBLUE, VALUEBLUE));
			}
			begin = i;
			currColor = img->at(i);
		}
	}
	if (currColor == RED)
	{
		land->push_back(new LandscapeElem(false, (i + begin - 1 - VIEW_ANGLE) / 2. / 360. * PI,
			(i - begin) / 360. * PI, HUERED, SATRED, VALUERED));
	}
	else if (currColor == BLUE)
	{
		land->push_back(new LandscapeElem(false, (i + begin - 1 - VIEW_ANGLE) / 2. / 360. * PI,
			(i - begin) / 360. * PI, HUEBLUE, SATBLUE, VALUEBLUE));
	}

	return land;
}

float DynamicModelColor::_getSimilarity(LandscapeElem* e1, LandscapeElem* e2)
{
	return exp(-pow(fabs(e1->hue - e2->hue) / 5, 2) - 
		pow(fabs(e1->sat - e2->sat) / 15, 2) -
		pow(fabs(e1->lum - e2->lum) / 15, 2) -
		pow(fabs(e1->center - e2->center) / (PI / 2), 2));
}