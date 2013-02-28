#ifndef DYNAMICMODELNOCOLOR_HPP
# define DYNAMICMODELNOCOLOR_HPP

# include "dynamicmodel.hpp"

class DynamicModelNoColor : public DynamicModel
{
public:
	DynamicModelNoColor(Image* goalViewImg);
protected:
	virtual Landscape* _imageToLandscape(Image* img);
	virtual float _getSimilarity(LandscapeElem* e1, LandscapeElem* e2);
};

#endif // !DYNAMICMODELNOCOLOR_HPP