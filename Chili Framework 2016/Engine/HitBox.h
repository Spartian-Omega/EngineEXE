#pragma once

#include "_2D_Vector.h"

class HitBox
{
public:
	HitBox();
	~HitBox();
	void Set(_2D_Point & centre, int & size);

	_2D_Point ClampToMoveableArea();

private:
	double * _x, * _y;
	int	  _size = 0;
};

