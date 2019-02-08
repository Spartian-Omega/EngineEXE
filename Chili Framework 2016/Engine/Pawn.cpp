#include "Pawn.h"
#include "Graphics.h"

Pawn::Pawn(_2D_Point p, Shape * s) : _centre(p) , _shape(s)
{
	////////////////
	_destroy = false;
	////////////////
}


Pawn::~Pawn()
{

}

void Pawn::Draw(Graphics & gfx)
{
	_shape->Draw(gfx, _centre);
}

void Pawn::UpdatePawn()
{

}

void Pawn::collisionDetected(Pawn * collidingPawn)
{

}