#include "dynamicradial.hpp"

DynamicRadial::DynamicRadial(Image* goalViewImg) :
	DynamicModel(goalViewImg)
{
	_goalViewLand = _imageToLandscape(goalViewImg);
}

Landscape* DynamicRadial::_imageToLandscape(Image* img)
{
	Landscape* land = new Landscape();	

	float begin = 0;
	int currColor = img->at(0);
	uint i = 0;
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

float DynamicRadial::_getSimilarity(LandscapeElem* e1, LandscapeElem* e2)
{
	return exp(-pow(fabs(e1->hue - e2->hue) / 5, 2) - 
		pow(fabs(e1->sat - e2->sat) / 15, 2) -
		pow(fabs(e1->lum - e2->lum) / 15, 2) -
		pow(fabs(e1->center - e2->center) / (PI / 2), 2));
}



void DynamicRadial::computeMove(Image* img)
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


	for (uint i = 0; i < _goalViewLand->size(); i++)
	{
		lTable.push_back(new std::vector<float>());
		lTable[i + 1]->push_back(0);
		pTable.push_back(new std::vector<float>());
		pTable[i + 1]->push_back(0);

		for (uint j = 0; j < land->size(); j++)
		{
			float sim = _getSimilarity(_goalViewLand->at(i), land->at(j));
			if (lTable[(i - 1) + 1]->at((j - 1) + 1) + sim >= lTable[i + 1]->at((j - 1) + 1) &&
				lTable[(i - 1) + 1]->at((j - 1) + 1) + sim >= lTable[(i - 1) + 1]->at(j + 1))
			{
				lTable[i + 1]->push_back(sim + lTable[(i - 1) + 1]->at((j - 1) + 1));
				pTable[i + 1]->push_back(1);
			}
			else if ((lTable[(i - 1) + 1]->at((j) + 1) >= lTable[i + 1]->at((j - 1) + 1)))
			{
				lTable[i + 1]->push_back(lTable[(i - 1) + 1]->at(j + 1));
				pTable[i + 1]->push_back(2);				
			}
			else
			{
				lTable[i + 1]->push_back(lTable[i + 1]->at((j - 1) + 1));
				pTable[i + 1]->push_back(3);				
			}
		}
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
				// TODO : add Proportionnal
				_x += -sin(_goalViewLand->at(i)->center)* 5 * fabs(_goalViewLand->at(i)->center - land->at(j)->center);
				_y += -cos(_goalViewLand->at(i)->center)* 5 * fabs(_goalViewLand->at(i)->center - land->at(j)->center);
			}
			else if((land->at(j)->center < _goalViewLand->at(i)->center))
			{
				_x += sin(_goalViewLand->at(i)->center)* 5 * fabs(_goalViewLand->at(i)->center - land->at(j)->center);
				_y += cos(_goalViewLand->at(i)->center)* 5 * fabs(_goalViewLand->at(i)->center - land->at(j)->center);
			}
			
			// //Compute Radial component
			if(land->size() <= 1)
			{
				if(_goalViewLand->at(i)->size > land->at(j)->size)
				{
					_x += cos(_goalViewLand->at(i)->center) * 2.5 * fabs(_goalViewLand->at(i)->size - land->at(j)->size);
					_y += -sin(_goalViewLand->at(i)->center) * 2.5 * fabs(_goalViewLand->at(i)->size - land->at(j)->size);
				}
				else if(_goalViewLand->at(i)->size < land->at(j)->size)
				{
					_x += -cos(_goalViewLand->at(i)->center) * 2.5 * fabs(_goalViewLand->at(i)->size - land->at(j)->size);
					_y += sin(_goalViewLand->at(i)->center) * 2.5 * fabs(_goalViewLand->at(i)->size - land->at(j)->size);
				}
			}
			// std::cout << i << " = " << j << std::endl;
			i--;
			j--;
			nbMatch++;
		}
		else if (pTable[i + 1]->at(j + 1) == 2)
			i--;
		else
			j--;
	}

	if (nbMatch != 0)
	{
		_x /= nbMatch;
		_y /= nbMatch;
	}
}