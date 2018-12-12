#pragma once
#include "_2D_Vector.h"
#include "Colors.h"

class Graphics;

class Shape
{
public:
	Shape();
	~Shape();

	virtual int QueryWidth();
	virtual int QueryHeight();
	virtual void Draw(Graphics & gfx, _2D_Point p);

	int QueryArea() { return _area; }
	void SetColour(Color c) { _colour = c; }
	Color GetColour() { return _colour; }

protected:
	int _area = 0;
	Color _colour = Color(255, 255, 255);
};

