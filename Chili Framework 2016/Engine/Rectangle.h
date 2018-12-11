#pragma once
#include "Shape.h"
class Rectangle :
	public Shape
{
public:
	Rectangle(int w, int h);
	~Rectangle();

	int QueryWidth() { return _width; }
	int QueryHeight() { return _height; }

protected:
	int _width;
	int _height;
};

