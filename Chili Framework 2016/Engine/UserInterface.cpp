#include "UserInterface.h"

#include <string>
#include <sstream>

#include "MainWindow.h"

#include "_2D_Vector.h"



UserInterface::UserInterface(MainWindow & wnd) : wnd(wnd)
{
}


UserInterface::~UserInterface()
{
}

MainWindow & UserInterface::QueryMainWindow() const
{
	return wnd;
}



void UserInterface::UIGo()
{
	_2D_Point mousePosition(0, 0);
if (wnd.mouse.LeftIsPressed()) {
	mousePosition.x = wnd.mouse.GetPosX();
	mousePosition.y = wnd.mouse.GetPosY();

	for (int i = 0; i < WAMNT; i++) {
		if (_Buttons[i].IsVisible()) {
			_Buttons[i].QueryHit(mousePosition);
		}
	}
	}
}
