#ifndef ROBOT_HPP
# define ROBOT_HPP

#include <vector>

#include "landscape.hpp"

#define VIEW_ANGLE 220
#define ROBOT_SIZE 40

typedef std::vector<int> Image;

class Robot
{
public:
  Robot(const std::vector<int>& goalView);
  ~Robot();

  void step(const std::vector<int>& view);
  float getMoveX();
  float getMoveY();

private:
	Landscape* _imageToLandscape(Image* img);

private:
  float _moveX;
  float _moveY;
};

#endif // !ROBOT_HPP
