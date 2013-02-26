#include "dynamicmodel.hpp"

#include <cstdlib>
#include <iostream>
#include <cmath>

Dynamicmodel::Dynamicmodel(Image* goalViewImg) :
	Model()
{
	_goalViewLand = _imageToLandscape(goalViewImg);
}
	
Dynamicmodel::~Dynamicmodel()
{

}

void Dynamicmodel::computeMove(Image* img)
{
	Landscape* land = _imageToLandscape(img);

	std::vector<std::vector<float>* > lTable;
	std::vector<std::vector<float>* > pTable;

	lTable.push_back(new std::vector<float>());
	pTable.push_back(new std::vector<float>());
	for (int j = -1; j < (int)land->size(); j++)
	{
		lTable[0]->push_back(0);
		pTable[0]->push_back(0);
	}


	for (int i = 0; i < _goalViewLand->size(); i++)
	{
		lTable.push_back(new std::vector<float>());
		lTable[i + 1]->push_back(0);
		pTable.push_back(new std::vector<float>());
		pTable[i + 1]->push_back(0);

		for (int j = 0; j < land->size(); j++)
		{
			if (lTable[(i - 1) + 1]->at((j - 1) + 1) >= lTable[i + 1]->at((j - 1) + 1) &&
				lTable[(i - 1) + 1]->at((j - 1) + 1) >= lTable[(i - 1) + 1]->at(j + 1))
			{
				lTable[i + 1]->push_back(_getSimilarity(_goalViewLand->at(i), land->at(j)) + lTable[(i - 1) + 1]->at((j - 1) + 1));
				pTable[i + 1]->push_back(1);
			}
			else if ((lTable[(i - 1) + 1]->at((j) + 1) >= lTable[i + 1]->at((j - 1) + 1)))
			{
				lTable[i + 1]->push_back(_getSimilarity(_goalViewLand->at(i), land->at(j)) + lTable[i + 1]->at((j - 1) + 1));
				pTable[i + 1]->push_back(2);				
			}
			else
			{
				lTable[i + 1]->push_back(_getSimilarity(_goalViewLand->at(i), land->at(j)) + lTable[(i - 1) + 1]->at(j + 1));
				pTable[i + 1]->push_back(3);				
			}
		}
	}

	for (int j = 0; j < land->size(); j++)
	{
		for (int i = 0; i < _goalViewLand->size(); i++)
		{
			std::cout << pTable[i + 1]->at(j + 1) << " ";
		}
		std::cout << std::endl;
	}

	_x = 0;
	_y = 0;

	int nbMatch = 0;
	int i = _goalViewLand->size() - 1;
	int j = land->size() - 1;
	while (pTable[i + 1]->at(j + 1) != 0)
	{
		if (pTable[i + 1]->at(j + 1) == 1)
		{
			if((land->at(j)->center > _goalViewLand->at(i)->center))
			{
				_x += -sin(land->at(j)->center);
				_y += cos(land->at(j)->center);
			}
			else if((land->at(j)->center < _goalViewLand->at(i)->center))
			{
				_x += sin(land->at(j)->center);
				_y += -cos(land->at(j)->center);
			}
			std::cout << i << " = " << j << std::endl;
			i--;
			j--;
			nbMatch++;
		}
		else if (pTable[i + 1]->at(j + 1) == 2)
			i--;
		else
			j--;
	}

	_x /= nbMatch;
	_y /= nbMatch;

}

Landscape* Dynamicmodel::_imageToLandscape(Image* img)
{
	Landscape* land = new Landscape();	

	int begin = 0;
	int currColor = img->at(0);
	int i;
	for (i = 0; i < img->size(); i++)
	{
		if (img->at(i) != currColor)
		{
			if (currColor == RED)
			{
				land->push_back(new LandscapeElem(false, (i + begin - 220) / 2. / 360. * PI,
					(i - begin - 110) / 360. * PI, HUERED, SATRED, VALUERED));
			}
			else if (currColor == BLUE)
			{
				land->push_back(new LandscapeElem(false, (i + begin - 220) / 2. / 360. * PI,
					(i - begin - 110) / 360. * PI, HUEBLUE, SATBLUE, VALUEBLUE));
			}
			begin = i;
			currColor = img->at(i);
		}
	}
	if (currColor == RED)
	{
		land->push_back(new LandscapeElem(false, (i + begin) / 2. / 360. * PI,
			(i - begin) / 360. * PI, HUERED, SATRED, VALUERED));
	}
	else if (currColor == BLUE)
	{
		land->push_back(new LandscapeElem(false, (i + begin) / 2. / 360. * PI,
			(i - begin) / 360. * PI, HUEBLUE, SATBLUE, VALUEBLUE));
	}

	return land;
}

float Dynamicmodel::_getSimilarity(LandscapeElem* e1, LandscapeElem* e2)
{
	return exp(-pow((e1->hue - e2->hue) / 5, 2) - 
		pow((e1->sat - e2->sat) / 15, 2) -
		pow((e1->lum - e2->lum) / 15, 2) -
		pow((e1->center - e2->center) / (PI / 2), 2));
}