#pragma once

#include "Widget.h"
#include "Button.h"

class MainWindow;


class UserInterface
{
public:
	UserInterface(MainWindow & wnd);
	~UserInterface();

	void UIGo();

	static int const WAMNT = 10; // Amount of each widgets per class.

	Widget _Widgets[10];
	Button _Buttons[10];

protected:
	MainWindow & wnd;
};

struct UIData
{
	Widget DWidgets[10];
	Button DButtons[10];

	void operator = (const UserInterface & UI) {
		for (int i = 0; i < UserInterface::WAMNT; i++) {
			DWidgets[i] = UI._Widgets[i];
			DButtons[i] = UI._Buttons[i];
		}
	}

};
