#include "Circle.h"



Circle::Circle(int r) : _radius(r)
{
	_area = PI * r * r;
}


Circle::~Circle()
{
}
