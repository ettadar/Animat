#ifndef DYNAMICMODELCOLOR_HPP
# define DYNAMICMODELCOLOR_HPP

# include "dynamicmodel.hpp"

class DynamicModelColor : public DynamicModel
{
public:
	DynamicModelColor(Image* goalViewImg);
protected:
	virtual Landscape* _imageToLandscape(Image* img);
	virtual float _getSimilarity(LandscapeElem* e1, LandscapeElem* e2);
};

#endif // !DYNAMICMODELCOLOR_HPP