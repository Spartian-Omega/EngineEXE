#pragma once
#include "Shape.h"

#define PI 3.14159265358979

class Circle :
	public Shape
{
public:
	Circle(int r);
	~Circle();

public:
	int QueryRadius() { return _radius; }
	
protected:
	int _radius;
};

