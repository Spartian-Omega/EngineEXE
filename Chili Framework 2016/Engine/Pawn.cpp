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

const void Pawn::Draw(Graphics & gfx, _2D_Point & campos)
{
	bool inScreenBounds = true;
	_2D_Point posNorm;
	if ((_centre.x - campos.x) < 400 - 50 && (_centre.x - campos.x) > -400 + 50) {
		posNorm.x = _centre.x - campos.x + 400;
	}
	else { inScreenBounds = false; }
	if ((_centre.y - campos.y) < 300 - 50 && (_centre.y - campos.y) > -300 + 50) {
		posNorm.y = _centre.y - campos.y + 300;
	}
	else { inScreenBounds = false; }
	if (inScreenBounds) {
		_shape->Draw(gfx, posNorm);
	}
}

void Pawn::UpdatePawn()
{

}

void Pawn::collisionDetected(Pawn * collidingPawn)
{

}