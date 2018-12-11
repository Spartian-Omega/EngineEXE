#include "Menu.h"
#include "GameState.h"
#include "Button.h"



Menu::Menu(GameState & g) : Level(g)
{
	_Buttons[0] = new Button(_2D_Point(400, 300));
}


Menu::~Menu()
{
}

void Menu::LevelGo(double dt)
{
	_GameState._widgetArray[0] = _Buttons[0];
	if (_Buttons[0]->QueryHit()) {
		_Buttons[0]->SetColour(Color(0, 255, 0));
		_Buttons[0]->Release();
	}
	else {
		_Buttons[0]->SetColour(Color(255, 0, 0));
	}
}

