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
	
	//Tangente component x & y
	
	float x = 0;
	float y = 0;
	
	int iBegin = landView->at(0)->gap ? 0 : 1;
	int jBegin = _goalViewLand->at(0)->gap ? 0 : 1;

	_gapOrLandmarkComputeMove(x, y, iBegin, jBegin, landView);
	_gapOrLandmarkComputeMove(x, y, abs(iBegin - 1), abs(jBegin - 1), landView);

	_x = x / landView->size();
	_y = y / landView->size();

	std::cout<<"taille de _x cc model "<<_x<<std::endl;
	std::cout<<"taille de _y cc model "<<_y<<std::endl;
	delete landView;
}

void CCmodel::print(Landscape* land)
{
	for(int i = 0; i < land->size(); i++)
	{
		std::cout << "objet numero " << i << " " << *(land->at(i)) << std::endl;
	}
}

Landscape* CCmodel::_imageToLandscape(Image* img)
{
	Landscape* land = new Landscape();
	for(int debut = 0; debut < img->size();)
	{
		std::cout<<" debut = "<< debut <<std::endl;
		if (img->at(debut) != 0)
		{int fin = debut;
			do{
				fin++;
			}while(fin < img->size() && img->at(fin) != 0 );
			std::cout<<" fin = "<< fin <<std::endl;
			LandscapeElem* object = new LandscapeElem(false,
				((((debut+fin-1)/2) - VIEW_ANGLE / 2)  / 360.) * 2 * PI,
		    	((float)(fin - debut) / 360) * 2 * PI);
			land->push_back(object);
			debut=fin;
		}//fin debut !=0
	
		else if (img->at(debut) == 0)
		{int fin = debut;
			do{
				fin++;
			}while(fin < img->size() && img->at(fin) == 0 );
			std::cout<<" fin = "<< fin <<std::endl;
			LandscapeElem* object = new LandscapeElem(true,
				((((debut+fin-1)/2) - VIEW_ANGLE / 2) / 360.) * 2 * PI,
				((float)(fin - debut) / 360) * 2 * PI);
			land->push_back(object);
			debut=fin;
		}//fin if ==0
	}//fin du for sur image
	print(land);
	return land;
}

void CCmodel::_gapOrLandmarkComputeMove(float& x, float& y, int iBegin, int jBegin, Landscape* landView)
{

	int i = iBegin;
	int j = jBegin;

	for (; i < landView->size(); i += 2)
	{
		while(j + 2 < _goalViewLand->size() && 
			fabs(landView->at(i)->center - _goalViewLand->at(j)->center) >  
			fabs(landView->at(i)->center - _goalViewLand->at(j + 2)->center))
		{
			j += 2;
		}

		// Compute tangential component
		if((landView->at(i)->center > _goalViewLand->at(j)->center))
		{
			x += -sin(landView->at(i)->center);
			y += cos(landView->at(i)->center);
		}
		else if((landView->at(i)->center < _goalViewLand->at(j)->center))
		{
			x += sin(landView->at(i)->center);
			y += -cos(landView->at(i)->center);
		}

		// Compute radial component
		if((landView->at(i)->size > _goalViewLand->at(j)->size))
		{
			y += -sin(landView->at(i)->center);
			x += -cos(landView->at(i)->center);
		}
		else if((landView->at(i)->size < _goalViewLand->at(j)->size))
		{
			y += sin(landView->at(i)->center);
			x += cos(landView->at(i)->center);
		}
	}
}
