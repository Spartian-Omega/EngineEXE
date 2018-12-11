#include "Menu.h"
#include "GameState.h"
#include "Button.h"



Menu::Menu(GameState & g) : Level(g)
{
	_Buttons[0] = new Button(_2D_Point(250, 300));
	_Buttons[1] = new Button(_2D_Point(550, 300));
}


Menu::~Menu()
{
	delete _GameState._widgetArray[0];
	delete _GameState._widgetArray[1];

	_GameState._widgetArray[0] = nullptr;
	_GameState._widgetArray[1] = nullptr;
}

void Menu::LevelGo(double dt)
{
	if (_Buttons[0] != NULL) {
		_GameState._widgetArray[0] = _Buttons[0];
		if (_Buttons[0]->QueryHit()) {
			_Buttons[0]->SetColour(Color(0, 255, 0));
			_Buttons[0]->Release();
			_buttonPressed[0] = true;
		}
		else {
			_Buttons[0]->SetColour(Color(255, 0, 0));
			_buttonPressed[0] = false;
		}
	}
	if (_Buttons[1] != NULL) {
		_GameState._widgetArray[1] = _Buttons[1];
		if (_Buttons[1]->QueryHit()) {
			_Buttons[1]->SetColour(Color(0, 255, 0));
			_Buttons[1]->Release();
			_buttonPressed[1] = true;
		}
		else {
			_Buttons[1]->SetColour(Color(0, 0, 255));
			_buttonPressed[1] = false;
		}
	}

	if (_buttonPressed[0]) {
		_nextLevel = true;
		_GameState.IsHost(true);
	}
	if (_buttonPressed[1]) {
		_nextLevel = true;
		_GameState.IsHost(false);
	}
}

