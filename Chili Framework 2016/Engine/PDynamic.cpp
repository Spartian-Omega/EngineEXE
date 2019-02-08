#include "PDynamic.h"



PDynamic::PDynamic(_2D_Point p, Shape * s) : Pawn(p, s)
{
	_path.p1 = p;
	_path.p2 = p;
	_dx = 0; _dy = 0;
	_dtx = 0; _dty = 0;
	_areaFriction = 0.0;
}


PDynamic::~PDynamic()
{
}

void PDynamic::UpdatePawn()
{

}

void PDynamic::AssignController(Controller * controller)
{
	MyController = controller;
}

void PDynamic::MoveHorizontal(int direction, double dt)
{

}

void PDynamic::MoveVertical(int direction, double dt)
{

}

void PDynamic::collisionDetected(Pawn * collidingPawn)
{

}
