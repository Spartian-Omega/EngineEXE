#pragma once
#include "Shape.h"
class Square :
	public Shape
{
public:
	Square(int s);
	~Square();

	int QueryWidth() { return _size; }
	int QueryHeight() { return _size; }

	void Draw(Graphics & gfx, _2D_Point p);

protected:
	int _size;
};

