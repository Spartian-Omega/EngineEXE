#include "PDefaultCharacter.h"
#include "Square.h"
#include "Map.h"

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

	if (_OnCeil && _dy < 0) {
		_dy = 0;
	}
	if (_OnSurface && _dy > 0) {
		_dy = 0;
	}
}

void PDefaultCharacter::CollisionDetected(Pawn * collidingPawn)
{
	//OutputDebugString(L"Hit! \n");
	if (MyController->GetTarget() == collidingPawn)
	{
		//	OutputDebugString(L"Hit Target! \n"); // This will cause a stutter with large amounts of pawns.
		_destroy = true;
	}
}

void PDefaultCharacter::TouchingSurface(Terrain * terra, const bool floor)
{
	if (terra == nullptr && !floor)
	{
		_OnSurface = false;
	}
	else if (terra == nullptr && floor)
	{
		_OnCeil = false;
	}
	else{
		if (*terra == TerraTypes::Grass && !floor) {
			_dy = 0;
			_dty = 0;
			_OnSurface = true;
		}
		else if (*terra == TerraTypes::Grass && floor) {
			_dy = 0;
			_dty = 0;
			_OnCeil = true;
		}
	}
}

void PDefaultCharacter::TouchingMapBoundary(bool a, bool b, bool c)
{
	if (c) {
		if (a && !b) { // top
			_boundaryTop = true;
		}
		else if (a && b) { // bottom
			_boundaryBottom = true;
		}
		else if (!a && b) { // left
			_boundaryLeft = true;
		}
		else if (!a && !b) { // right
			_boundaryRight = true;
		}
	}
	else {
		if (a && !b) { // top
			_boundaryTop = false;
		}
		else if (a && b) { // bottom
			_boundaryBottom = false;
		}
		else if (!a && b) { // left
			_boundaryLeft = false;
		}
		else if (!a && !b) { // right
			_boundaryRight = false;
		}
	}
}
