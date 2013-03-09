#ifndef DYNAMICMODEL_HPP
# define DYNAMICMODEL_HPP

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>

#include "type.hpp"
#include "model.hpp"
#include "landscape.hpp"


class DynamicModel : public Model
{
public:
	DynamicModel(Image* goalViewImg);
	~DynamicModel();
	void computeMove(Image* img);

protected:
	virtual Landscape* _imageToLandscape(Image* img) = 0;
	virtual float _getSimilarity(LandscapeElem* e1, LandscapeElem* e2) = 0;
};

#include "dynamicmodelnocolor.hpp"
#include "dynamicmodelcolor.hpp"
#include "dynamicradial.hpp"

#endif // !DYNAMICMODEL_HPP
