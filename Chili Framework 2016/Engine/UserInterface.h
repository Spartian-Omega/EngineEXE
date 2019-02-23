#pragma once

#include "Widget.h"
#include "Button.h"

class MainWindow;


class UserInterface
{
public:
	UserInterface(MainWindow & wnd);
	~UserInterface();

	MainWindow & QueryMainWindow() const;

	void UIGo();


	static int const WAMNT = 10; // Amount of each widgets per class.

	Widget _Widgets[WAMNT];
	Button _Buttons[WAMNT];

protected:
	MainWindow & wnd;
};

struct UIData
{
	Widget DWidgets[UserInterface::WAMNT];
	Button DButtons[UserInterface::WAMNT];

	void Clear() {
		for (int i = 0; i < UserInterface::WAMNT; i++) {
			DWidgets[i] = Widget();
			DButtons[i] = Button();
		}
	}

	void operator = (const UserInterface & UI) {
		for (int i = 0; i < UserInterface::WAMNT; i++) {
			DWidgets[i] = UI._Widgets[i];
			DButtons[i] = UI._Buttons[i];
		}
	}

};
