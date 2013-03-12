#ifndef CCMODEL_HPP
# define CCMODEL_HPP

#include <vector>

#include "model.hpp"

class CCmodel : public Model
{
public :
	CCmodel(Image* goalViewImg);
	~CCmodel();
	void computeMove(Image* img);
private :
	Landscape* _imageToLandscape(Image* img);
	void _gapOrLandmarkComputeMove(float& x, float& y, int iBegin, int jBegin, Landscape* landView);
};



#endif // !CCMODEL_HPP
