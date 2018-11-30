#include "HitBox.h"



HitBox::HitBox()
{

}


HitBox::~HitBox()
{

}

void HitBox::Set(_2D_Point & centre, int & sizeW, int & sizeH)
{
	_x = &centre.x;
	_y = &centre.y;
	_sizeH = sizeH;
	_sizeW = sizeW;
}


_2D_Point HitBox::ClampToMoveableArea()
{
	double x = *_x , y = * _y;
	_2D_Point point;
	if ((*_x - (_sizeW / 2)) <= 0) {
		x = 2 + (_sizeW / 2);
	}
	else if ((*_x + (_sizeW / 2)) >= 798) {
		x = 798 - (_sizeW / 2);
	}
	else{
		
	}
	if ((*_y - (_sizeH / 2)) <= 0) {
		y = 2 + (_sizeH / 2);
	}
	else if ((*_y + (_sizeH / 2)) >= 598) {
		y = 598 - (_sizeH / 2);
	}
	else {
		
	}

	point.x = x;
	point.y = y;

	return point;
}