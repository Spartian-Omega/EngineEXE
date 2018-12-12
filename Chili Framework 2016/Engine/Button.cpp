#include "Button.h"
#include "Square.h"

#include "_2D_Vector.h"

#include "Graphics.h"



Button::Button()
{
}

Button::Button(_2D_Point p) : Widget(p, new Square(100))
{	
}


Button::~Button()
{
}

bool Button::QueryHit()
{
	return _isPressed;
}

bool Button::QueryHit(_2D_Point h)
{
	int btop, bbottom, bleft, bright;

	btop = _position.y + _shape->QueryHeight() /2;
	bbottom = _position.y - _shape->QueryHeight() / 2;
	bleft = _position.x - _shape->QueryWidth() / 2;
	bright = _position.x + _shape->QueryWidth() / 2;

	return (_isPressed = (h.y < btop && h.y > bbottom && h.x > bleft && h.x < bright));
}

void Button::Release()
{
	_isPressed = false;
}



void Button::Draw(Graphics & gfx)
{
	_shape->Draw(gfx, _position);
}
