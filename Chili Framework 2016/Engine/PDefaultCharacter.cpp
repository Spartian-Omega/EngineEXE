#include "PDefaultCharacter.h"
#include "Square.h"

/// Static Variable Declarations
const int	PDefaultCharacter::_maxspeed = 500;
const float PDefaultCharacter::_a1 = 0.1;	//acceleration interval
///

PDefaultCharacter::PDefaultCharacter(_2D_Point p) : PCharacter(p, new Square(10))
{
	_areaFriction = 0.05;
}


PDefaultCharacter::~PDefaultCharacter()
{
}



void PDefaultCharacter::UpdatePawn()
{
	_path.p1.x = _path.p2.x;
	_path.p1.y = _path.p2.y;
	if (_dx > 0) {
		_centre.x += _dx;
	}
	else if (_dx < 0) {
		_centre.x += _dx;
	}
	if (_dy > 0) {
		_centre.y += _dy;
	}
	else if (_dy < 0) {
		_centre.y += _dy;
	}
	/// Redo the following for clamping to the map boundaries and colliding with terrain.

	_2D_Point point = _hbox.ClampToMoveableArea(_centre, QuerySizeW(), QuerySizeH());
	if ((_centre.x) != point.x || (_centre.y != point.y)) {
		_centre.x = point.x;
		_centre.y = point.y;
		_dx = 0; _dtx = 0;
		_dy = 0; _dty = 0;
	}

	///
	_path.p2.x = _centre.x;
	_path.p2.y = _centre.y;
}

void PDefaultCharacter::MoveHorizontal(int direction, double dt)
{
	switch (direction)
	{
	case 1:
		if (_dtx < 0) {
			_dtx += 4 * dt;
		}
		else {
			_dtx += dt;
		}
		//OutputDebugString(L"Right Key Is Pressed\n");
		break;
	case -1:
		if (_dtx > 0) {
			_dtx -= 4 * dt;
		}
		else {
			_dtx -= dt;
		}
		//OutputDebugString(L"Left Key Is Pressed\n");
		break;
	case 0:
		_dtx -= (_dtx * _areaFriction);
		break;
	default:
		break;
	}

	if (_dtx > 1) { _dtx = 1; }
	else if (_dtx < -1) { _dtx = -1; }

	if (_dtx > 0) {
		_dx = _maxspeed * (_dtx / (_dtx + _a1)) * (dt);
		// _dx = maxspeed * dx/dt * framescale	(maxspeed = maximum pixels to be traveresed in one second)
		//										(dx/dt = velocity function)
		//										(framescale = frame time interval)
	}
	else if (_dtx < 0) {
		_dx = -_maxspeed * (_dtx / (_dtx - _a1)) * (dt);
	}
}

void PDefaultCharacter::MoveVertical(int direction, double dt)
{
	switch (direction)
	{
	case 1:
		if (_dty < 0) {
			_dty += 4 * dt;
		}
		else {
			_dty += dt;
		}
		//OutputDebugString(L"Down Key Is Pressed\n");
		break;
	case -1:
		if (_dty > 0) {
			_dty -= 4 * dt;
		}
		else {
			_dty -= dt;
		}
		//OutputDebugString(L"Up Key Is Pressed\n");
		break;
	case 0:
		_dty -= (_dty * _areaFriction);
		break;
	default:
		break;
	}
	if (_dty > 1) { _dty = 1; }
	else if (_dty < -1) { _dty = -1; }

	if (_dty > 0) {
		_dy = _maxspeed * (_dty / (_dty + _a1)) * (dt);
	}
	else if (_dty < 0) {
		_dy = -_maxspeed * (_dty / (_dty - _a1)) * (dt);
	}
}

void PDefaultCharacter::collisionDetected(Pawn * collidingPawn)
{
	//OutputDebugString(L"Hit! \n");
	if (MyController->GetTarget() == collidingPawn)
	{
		//	OutputDebugString(L"Hit Target! \n"); // This will cause a stutter with large amounts of pawns.
		_destroy = true;
	}
}