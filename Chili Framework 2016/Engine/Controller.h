#pragma once


#include "MainWindow.h"
#include <string>
#include <sstream>


class Controller
{
public:
	Controller(class PDynamic * pawn);
	~Controller();

	virtual void ControllerGo(double dt);
	virtual void SetTarget(class Pawn * targetPawn);
	virtual Pawn * GetTarget();

protected:
	PDynamic * myPawn;

	std::wstring _debug_wstream;

};

