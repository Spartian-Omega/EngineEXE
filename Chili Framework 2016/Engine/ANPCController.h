#pragma once
#include "Controller.h"
class ANPCController :
	public Controller
{
public:
	ANPCController(class Pawn * pawn);
	~ANPCController();

	void ControllerGo(double dt);
	void SetTarget(class Pawn * targetPawn);
	Pawn * GetTarget();
protected:
	void setPawnSpeed(double dt);
	Pawn * _TargetPawn;
};

