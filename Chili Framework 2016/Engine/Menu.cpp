#include "Menu.h"

#include "Widget.h"
#include "Button.h"
#include "Shape.h"
#include "_2D_Vector.h"

#include "MainWindow.h"


Menu::Menu(MainWindow & wnd): Stage(wnd)
{
	_UI._Buttons[0] = Button(_2D_Point(250, 300));
	_UI._Buttons[0].SetVisibility(true);
	_UI._Buttons[1] = Button(_2D_Point(550, 300));
	_UI._Buttons[1].SetVisibility(true);
}


Menu::~Menu()
{

}

void Menu::StageGo(double dt)
{
	UpdateUI(dt);
}

void Menu::UpdateUI(double dt)
{
	_UI.UIGo();
	if (_UI._Buttons[0].IsVisible()) {
		if (_UI._Buttons[0].QueryHit()) {
			_UI._Buttons[0].SetColour(Color(0, 255, 0));
			_UI._Buttons[0].Release();
			_STAGEEND = true;
		}
		else {
			_UI._Buttons[0].SetColour(Color(255, 0, 0));
		}
	}
	if (_UI._Buttons[1].IsVisible()) {
		if (_UI._Buttons[1].QueryHit()) {
			_UI._Buttons[1].SetColour(Color(0, 255, 0));
			_UI._Buttons[1].Release();
			_STAGEEND = true;
		}
		else {
			_UI._Buttons[1].SetColour(Color(0, 0, 255));
		}
	}
}

