#pragma once
#include "Controller.h"
class APlayerController :
	public Controller
{
public:
	APlayerController(class Pawn * pawn, class MainWindow & wnd);
	~APlayerController();

	void ControllerGo(double dt);
	Pawn * GetTarget();

	bool ControlIsPressed() { return _ctrlPressed; }

protected:
	MainWindow& wnd;
	bool _ctrlPressed = false;
};

