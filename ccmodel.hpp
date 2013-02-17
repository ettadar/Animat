#ifndef CCMODEL_HPP
# define CCMODEL_HPP

#include <vector>

#include "model.hpp"
#include "landscape.hpp"


class CCmodel : public Model
{
public :
	CCmodel(Image* goalViewImg);
	~CCmodel();
	void computeMove(Image* img);
	void Affiche(Landscape* land);
private :
	Landscape* _imageToLandscape(Image* img);
	//Landscape* _goalViewLand;
};

#endif // !CCMODEL_HPP
