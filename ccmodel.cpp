#include "ccmodel.hpp"

#include <cstdlib>
#include <iostream>
#include <cmath>

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
	float x = 0;
	float y = 0;
	int j = 0;
	for (int i = 0; i < landView->size(); i++)
	{
		while(j + 1 < _goalViewLand->size() && 
				abs(landView->at(i)->center - _goalViewLand->at(j)->center) >  
				abs(landView->at(i)->center - _goalViewLand->at(j+1)->center))
		{
			j++;
		}
		if((landView->at(i)->center - _goalViewLand->at(j)->center) > 0)
		{
			y += -cos(landView->at(i)->center);
			x += sin(landView->at(i)->center);
		}
		else if((landView->at(i)->center - _goalViewLand->at(j)->center) < 0)
		{
			y += cos(landView->at(i)->center);
			x += -sin(landView->at(i)->center);
		}
	
	}//fin du for i
	
	_x = x / landView->size();
	_y = y / landView->size();
	std::cout<<"taille de x cc model "<<_x<<std::endl;
	std::cout<<"taille de y cc model "<<_y<<std::endl;
	delete landView;
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

std::ostream & operator<< (std::ostream &o, LandscapeElem& elem)
{
	o << " objet "<< elem.gap << " centre " << elem.center << " angle " << ((elem.center - (VIEW_ANGLE / 2)) / 360 ) * 2 * PI << " taille de l'objet " << elem.size;
	return o;
}

void CCmodel::print(Landscape* land)
{
	for(int i = 0; i < land->size(); i++)
	{
		std::cout << "objet numero " << i << " " << *(land->at(i)) << std::endl;
	}
}





