#include "Controller.h"
#include "PDynamic.h"
#include "MainWindow.h"



Controller::Controller(PDynamic * pawn)
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




