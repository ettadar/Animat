#ifndef MODEL_HPP
# define MODEL_HPP

#include <vector>

#include "type.hpp"
#include "type.hpp"
#include "landscape.hpp"

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

#endif // !MODEL_HPP

