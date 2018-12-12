#pragma once

#include "_2D_Vector.h"
#include "Shape.h"
#include "Colors.h"

class Widget
{
public:
	Widget();
	Widget(_2D_Point p, Shape * s);
	~Widget();

	void SetPosition(_2D_Point p) { _position = p; }
	void SetShape(Shape * s) { _shape = s; }

	Color GetColour(){ return _colour; }
	void SetColour(Color c){ _colour = c; }

	void SetVisibility(bool b) { _isVisible = b; }
	bool IsVisible() { return _isVisible; }

	virtual bool QueryHit() { return false; }
	virtual void Draw(class Graphics & gfx) {}

protected:
	bool _isVisible = false;

	_2D_Point _position;
	Shape * _shape = nullptr;

	Color _colour = Color(255, 255, 255);
};

