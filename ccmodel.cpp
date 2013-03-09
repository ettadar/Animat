#include "ccmodel.hpp"

#include <cstdlib>
#include <iostream>
#include <cmath>

std::ostream & operator<< (std::ostream &o, LandscapeElem& elem)
{
	o << " objet "<< elem.gap << " centre " << elem.center << " taille de l'objet " << elem.size;
	return o;
}

CCmodel::CCmodel(Image* goalViewImg) : 
	Model()
	 
{
	_goalViewLand = _imageToLandscape(goalViewImg);
}

CCmodel::~CCmodel()
{

}

void CCmodel::computeMove(Image* img)
{
	Landscape* landView = _imageToLandscape(img);

	// for (int i = 0; i < landView->size(); i++)
	// 	std::cout << *(landView->at(i)) << std::endl;
	// std::cout << std::endl;
	
	//Tangente component x & y
	
	float x = 0;
	float y = 0;
	
	int iBegin = _goalViewLand->at(0)->gap ? 0 : 1;
	int jBegin = landView->at(0)->gap ? 0 : 1;

	_gapOrLandmarkComputeMove(x, y, iBegin, jBegin, landView);
	_gapOrLandmarkComputeMove(x, y, abs(iBegin - 1), abs(jBegin - 1), landView);

	_x = x / (float)(_goalViewLand->size() * 2);
	_y = y / (float)(_goalViewLand->size() * 2);

	//std::cout<<"taille de _x cc model "<<_x<<std::endl;
	//std::cout<<"taille de _y cc model "<<_y<<std::endl;
	delete landView;
}

void CCmodel::print(Landscape* land)
{
	for(uint i = 0; i < land->size(); i++)
	{
		std::cout << "objet numero " << i << " " << *(land->at(i)) << std::endl;
	}
}

Landscape* CCmodel::_imageToLandscape(Image* img)
{
	Landscape* land = new Landscape();
	int lastPixelColor = img->at(0);
	int lastObjBegin = 0;

	uint i = 0;
	for (; i < img->size(); ++i)
	{
		if (img->at(i) == lastPixelColor)
			continue;

		if (img->at(i) != BLACK && lastPixelColor != BLACK)
		{
			lastPixelColor = img->at(i);
			continue;
		}


		LandscapeElem* object = new LandscapeElem(lastPixelColor == BLACK,
			((((lastObjBegin + i - 1) / 2.) - VIEW_ANGLE / 2)  / 360.) * 2 * PI,
			((float)(i - lastObjBegin) / 360.) * 2 * PI);
		land->push_back(object);
		lastObjBegin = i;
		lastPixelColor = img->at(i);
	}

	LandscapeElem* object = new LandscapeElem(lastPixelColor == BLACK,
		((((lastObjBegin + i - 1) / 2.) - VIEW_ANGLE / 2)  / 360.) * 2 * PI,
		((float)(i - lastObjBegin) / 360.) * 2 * PI);
	land->push_back(object);
	return land;
}

void CCmodel::_gapOrLandmarkComputeMove(float& x, float& y, int iBegin, int jBegin, Landscape* landView)
{

	uint j = jBegin;
	if (landView->size() > j)
	{
		for (uint i = iBegin; i < _goalViewLand->size(); i += 2)
		{
			while(j + 2 < landView->size() && 
				fabs(_goalViewLand->at(i)->center - landView->at(j)->center) >  
				fabs(_goalViewLand->at(i)->center - landView->at(j + 2)->center))
			{
				j += 2;
			}

			//Compute tangential component
			if(_goalViewLand->at(i)->center > landView->at(j)->center)
			{
				x += sin(_goalViewLand->at(i)->center) * 5 * fabs(_goalViewLand->at(i)->center - landView->at(j)->center);
				y += cos(_goalViewLand->at(i)->center) * 5 * fabs(_goalViewLand->at(i)->center - landView->at(j)->center);
			}
			else if(_goalViewLand->at(i)->center < landView->at(j)->center)
			{
				x += -sin(_goalViewLand->at(i)->center) * 5 * fabs(_goalViewLand->at(i)->center - landView->at(j)->center);
				y += -cos(_goalViewLand->at(i)->center) * 5 * fabs(_goalViewLand->at(i)->center - landView->at(j)->center);
			}
			//Compute Radial component
			if(_goalViewLand->at(i)->size > landView->at(j)->size)
			{
				x += cos(_goalViewLand->at(i)->center) * 2.5 * fabs(_goalViewLand->at(i)->size - landView->at(j)->size);
				y += -sin(_goalViewLand->at(i)->center) * 2.5 * fabs(_goalViewLand->at(i)->size - landView->at(j)->size);
			}
			else if(_goalViewLand->at(i)->size < landView->at(j)->size)
			{
				x += -cos(_goalViewLand->at(i)->center) * 2.5 * fabs(_goalViewLand->at(i)->size - landView->at(j)->size);
				y += sin(_goalViewLand->at(i)->center) * 2.5 * fabs(_goalViewLand->at(i)->size - landView->at(j)->size);
			}
		}
	}
}
