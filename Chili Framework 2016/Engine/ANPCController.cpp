#include "ANPCController.h"
#include <cmath>



ANPCController::ANPCController(Pawn * pawn) : Controller(pawn)
{
	myPawn->SetColour(Color(0,0,0));
}


ANPCController::~ANPCController()
{
}

void ANPCController::SetTarget(Pawn * targetPawn)
{
	_TargetPawn = targetPawn;
}

void ANPCController::CyclePawnColour()
{
//	Color c(25 * _cTimer, 0 * _cTimer, 50 * _cTimer);
	Color c(50 * _cTimer + 50, 0, 25 * _cTimer + 50);
	myPawn->SetColour(c);
}

Pawn * ANPCController::GetTarget()
{
	return _TargetPawn;
}

void ANPCController::ControllerGo(double dt)
{
	setPawnSpeed(dt);
	_cTimer += dt;
	CyclePawnColour();
	myPawn->UpdatePawn();
}

void ANPCController::setPawnSpeed(double dt)
{
	//
	if (_TargetPawn)
	{
		_2D_Point currentpos = myPawn->QueryPosition();
		_2D_Point targetpos = _TargetPawn->QueryPosition();
		_2D_Vector vector2target;
		vector2target.p1 = currentpos;
		vector2target.p2 = targetpos;
		double xdisplacment = currentpos.x - targetpos.x;
		double ydisplacment = currentpos.y - targetpos.y;
		double targetdisplacment = vector2target.Length();
		double xdt = (xdisplacment / targetdisplacment) * dt;
		double ydt = (ydisplacment / targetdisplacment) * dt;
		//
		if (xdt < 0) {
			myPawn->MoveHorizontal(1, abs(xdt));
		}
		else {
			myPawn->MoveHorizontal(-1, abs(xdt));
		}
		if (ydt < 0) {
			myPawn->MoveVertical(1, abs(ydt));
		}
		else {
			myPawn->MoveVertical(-1, abs(ydt));
		}
	}
}
