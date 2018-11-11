#include "Controller.h"
#include "MainWindow.h"



Controller::Controller(Pawn * pawn)
{
	myPawn = pawn;
}


Controller::~Controller()
{
}

void Controller::ControllerGo(double dt)
{

}

void Controller::SetTarget(Pawn * targetPawn)
{
}

Pawn * Controller::GetTarget()
{
	return nullptr;
}




