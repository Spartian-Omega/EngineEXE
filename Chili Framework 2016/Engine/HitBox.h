#pragma once

#include "_2D_Vector.h"

class HitBox
{
public:
	HitBox();
	~HitBox();
	void Set(_2D_Point & centre, int & sizeW, int & sizeH);

	_2D_Point ClampToMoveableArea();

private:
	double * _x, * _y;
	int	  _sizeH = 0, _sizeW = 0;
};

