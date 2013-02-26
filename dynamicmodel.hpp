#ifndef DYNAMICMODEL_HPP
# define DYNAMICMODEL_HPP

#include <vector>

#include "type.hpp"
#include "model.hpp"
#include "landscape.hpp"


class Dynamicmodel : public Model
{
public:
	Dynamicmodel(Image* goalViewImg);
	~Dynamicmodel();
	void computeMove(Image* img);

protected:
	Landscape* _imageToLandscape(Image* img);
	virtual float _getSimilarity(LandscapeElem* e1, LandscapeElem* e2);
};

#endif // !DYNAMICMODEL_HPP
