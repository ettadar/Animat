#include "dynamicmodelnocolor.hpp"

DynamicModelNoColor::DynamicModelNoColor(Image* goalViewImg) :
	DynamicModel(goalViewImg)
{
	_goalViewLand = _imageToLandscape(goalViewImg);
}

Landscape* DynamicModelNoColor::_imageToLandscape(Image* img)
{
	Landscape* land = new Landscape();	

	float begin = 0;
	bool color = img->at(0);
	uint i = 0;
	for (i = 0; i < img->size(); i++)
	{
		if ((bool)img->at(i) != color)
		{
			if (color)
			{
				land->push_back(new LandscapeElem(false, (i + begin - 1 - VIEW_ANGLE) / 2. / 360. * PI,
					(i - begin) / 360. * PI));
			}
			begin = i;
			color = img->at(i);
		}
	}
	if (color)
	{
				land->push_back(new LandscapeElem(false, (i + begin - 1 - VIEW_ANGLE) / 2. / 360. * PI,
					(i - begin) / 360. * PI));
	}

	return land;
}

float DynamicModelNoColor::_getSimilarity(LandscapeElem* e1, LandscapeElem* e2)
{
	return exp(-pow(fabs(e1->center - e2->center) / (PI / 2), 2));
}