#ifndef DYNAMICRADIAL_HPP
# define DYNAMICRADIAL_HPP

# include "dynamicmodel.hpp"

class DynamicRadial : public DynamicModel
{
public:
	DynamicRadial(Image* goalViewImg);
	void computeMove(Image* img);
protected:
	virtual Landscape* _imageToLandscape(Image* img);
	virtual float _getSimilarity(LandscapeElem* e1, LandscapeElem* e2);
};

#endif // !DYNAMICRADIAL_HPP