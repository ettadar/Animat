#ifndef CYLINDER_HPP
# define CYLINDER_HPP

#define NB_COLOR 3
#define BLACK 0
#define RED 1
#define BLUE 2

struct Cylinder
{
	Cylinder(float x, float y, int color, float r) :
	x(x), y(y), color(color), r(r) {};
	float x;
	float y;
	int color;
	float r;
};

#endif // !CYLINDER_HPP
