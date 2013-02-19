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

}

Landscape* Dynamicmodel::_imageToLandscape(Image* img)
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
	//print(land);
	return land;
}
