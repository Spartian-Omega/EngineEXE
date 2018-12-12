#include "Square.h"
#include "Graphics.h"
#include "Colors.h"

Square::Square(int s) : _size(s)
{
	_area = s * s;
}


Square::~Square()
{
}

void Square::Draw(Graphics & gfx, _2D_Point p)
{
	gfx.DrawRectangle(p.x, p.y, _size , _size, _colour);
}
