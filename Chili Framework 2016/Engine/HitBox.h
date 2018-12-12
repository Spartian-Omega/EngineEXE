#pragma once

#include "_2D_Vector.h"

class HitBox
{
public:
	HitBox();
	~HitBox();

	_2D_Point ClampToMoveableArea(_2D_Point c, int w, int h);
};

