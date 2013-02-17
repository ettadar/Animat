#ifndef ROBOT_HPP
# define ROBOT_HPP

#include <vector>

#include "type.hpp"
#include "model.hpp"

class Robot
{
public:
  Robot(Model* model);
  ~Robot();

  void step(Image* img);
  float getMoveX();
  float getMoveY();



private:
	Model* _model;
  float _moveX;
  float _moveY;
};

#endif // !ROBOT_HPP
