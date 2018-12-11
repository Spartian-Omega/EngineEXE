#pragma once


#include "MainWindow.h"
#include <string>
#include <sstream>


class Controller
{
public:
	Controller(class Pawn * pawn);
	~Controller();

	virtual void ControllerGo(double dt);
	virtual void SetTarget(class Pawn * targetPawn);
	virtual Pawn * GetTarget();

protected:
	Pawn * myPawn;

	std::wstring _debug_wstream;

};

