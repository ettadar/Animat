#ifndef TYPE_HH
# define TYPE_HH

#include <iostream>


#define VIEW_ANGLE 220
#define ROBOT_SIZE 40
#define PI 3.141592653589

#define NB_COLOR 4
#define BLACK 0
#define RED 1
#define BLUE 2
#define GREEN 3

#define HUERED 0
#define SATRED 100
#define VALUERED 100

#define HUEBLUE 240
#define SATBLUE 100
#define VALUEBLUE 100

#define UNKNOWN 0
#define GOOD 1
#define BAD 2


#define VIEW_DISPLAY_RATIO 2

#define SIZEPIXEL 20.0
#define SIZE_ARROW 4

#define KNOWN_POS_TOL 100
#define OK_POS_TOL 10

typedef std::vector<int> Image;

#endif // !TYPE_HH
