#pragma once
#include "Widget.h"


class Button :
	public Widget
{
public:
	Button();
	Button(_2D_Point p);
	~Button();

	bool QueryHit();
	bool QueryHit(_2D_Point h);

	void Release();
	
	void Draw(class Graphics & gfx);


protected:
	bool _isPressed = false;

};

