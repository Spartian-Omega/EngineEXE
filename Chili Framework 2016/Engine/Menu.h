#pragma once

#include "Level.h"
#include "Widget.h"
#include "Button.h"
#include "Shape.h"


class Menu :
	public Level
{
public:
	Menu(class GameState & g);
	~Menu();
	
	void LevelGo(double dt);

protected:
	Widget * _Widgets[10];
	Button * _Buttons[10];



};

