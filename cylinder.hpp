#ifndef CYLINDER_HPP
# define CYLINDER_HPP

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
