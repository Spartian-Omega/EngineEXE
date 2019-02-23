#include "Collision.h"



Collision::Collision()
{

}


Collision::~Collision()
{

}


_2D_Point Collision::ClampToMoveableArea(_2D_Point c, int w, int h)
{
	double x = c.x , y = c.y;
	_2D_Point point;
	if ((c.x - (w / 2)) <= 0) {
		x = 2 + (w / 2);
	}
	else if ((c.x + (w / 2)) >= 798) {
		x = 798 - (w / 2);
	}
	else{
		
	}
	if ((c.y - (h / 2)) <= 0) {
		y = 2 + (h / 2);
	}
	else if ((c.y + (h / 2)) >= 598) {
		y = 598 - (h / 2);
	}
	else {
		
	}

	point.x = x;
	point.y = y;

	return point;
}