#ifndef DYNAMICRADIALONEOBJECT_HPP
# define DYNAMICRADIALONEOBJECT_HPP

# include "dynamicmodel.hpp"

class DynamicRadialoneobject : public DynamicModel
{
public:
	DynamicRadialoneobject(Image* goalViewImg);
	void computeMove(Image* img);
protected:
	virtual Landscape* _imageToLandscape(Image* img);
	virtual float _getSimilarity(LandscapeElem* e1, LandscapeElem* e2);
};

#endif // !DYNAMICRADIALONEOBJECT_HPP