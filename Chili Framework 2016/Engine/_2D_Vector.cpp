#include "_2D_Vector.h"
#include <cmath>

_2D_Vector::_2D_Vector()
{

}

_2D_Vector::_2D_Vector(_2D_Point p1, _2D_Point p2)
{

}

_2D_Vector::~_2D_Vector()
{

}

double _2D_Vector::Length()
{
	_2D_Point centreDisplacment = p1 - p2;
	return sqrt(centreDisplacment.x*centreDisplacment.x + centreDisplacment.y * centreDisplacment.y);
}
