#ifndef DYNAMICMODEL_HPP
# define DYNAMICMODEL_HPP

#include <vector>

#include "type.hpp"
#include "model.hpp"
#include "landscape.hpp"


class Dynamicmodel : public Model
{
public :
	Dynamicmodel(Image* goalViewImg);
	~Dynamicmodel();
	void computeMove(Image* img);
	//void print(Landscape* land);
private :
	Landscape* _imageToLandscape(Image* img);
	//Landscape* _goalViewLand;
};

#endif // !DYNAMICMODEL_HPP
