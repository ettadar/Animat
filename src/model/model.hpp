#ifndef MODEL_HPP
# define MODEL_HPP

#include <vector>
#include <cmath>
#include <cstdlib>

#include "../landscape.hpp"
#include "../const.hpp"

class Model
{
public:
	Model() {};
	~Model() {};
	virtual void computeMove(Image* img) = 0;
	float getMoveX() {return _x;};
	float getMoveY() {return _y;};
protected:
	virtual Landscape* _imageToLandscape(Image* img) = 0;
	Landscape* _goalViewLand;
	float _x;
	float _y;

};

#include "ccmodel.hpp"
#include "dynamicmodel.hpp"

#endif // !MODEL_HPP

