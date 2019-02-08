#pragma once
#include "Controller.h"
class ANPCController :
	public Controller
{
public:
	ANPCController(class PDynamic * pawn);
	~ANPCController();

	void ControllerGo(double dt);
	void SetTarget(class Pawn * targetPawn);
	void CyclePawnColour();

	Pawn * GetTarget();
protected:
	void setPawnSpeed(double dt);
	Pawn * _TargetPawn;

	double _cTimer;
};
