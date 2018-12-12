#include "Widget.h"



Widget::Widget()
{
	_position = _2D_Point(400.0, 300.0);
}

Widget::Widget(_2D_Point p, Shape * s) : _position(p) , _shape(s)
{

}


Widget::~Widget()
{
}



