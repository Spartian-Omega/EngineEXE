#pragma once
#include "Pawn.h"
class PStatic :
	public Pawn
{
public:
	PStatic(_2D_Point p, Shape * s);
	~PStatic();
};

