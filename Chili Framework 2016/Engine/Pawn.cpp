#include "Pawn.h"



Pawn::Pawn(int x, int y, int size)
{
	////////////////
	_destroy = false;
	////////////////

	_centre.x = x;
	_centre.y = y;
	_size = size;
	MyHitBox.Set(_centre, _size);
	
	_path.p1.x = x;
	_path.p1.y = y;
	_path.p2.x = x;
	_path.p2.y = y;

	_areaFriction = 0.05;
	_dx = 0; _dy = 0;
	_dtx = 0; _dty = 0;

	_maxspeed = 500;
	_acci = 0.1;


}


Pawn::~Pawn()
{

}

void Pawn::AssignController(Controller * controller)
{
	MyController = controller;
}

void Pawn::MoveHorizontal(int direction, double dt)
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

	if		(_dtx > 1)	{ _dtx = 1; }
	else if (_dtx < -1) { _dtx = -1; }

	if (_dtx > 0) {
		_dx = _maxspeed * (_dtx / (_dtx + _acci)) * (dt);
		// _dx = maxspeed * dx/dt * framescale	(maxspeed = maximum pixels to be traveresed in one second)
		//										(dx/dt = velocity function)
		//										(framescale = frame time interval)
	}
	else if (_dtx < 0) {
		_dx = -_maxspeed * (_dtx / (_dtx - _acci)) * (dt);
	}

}

void Pawn::MoveVertical(int direction, double dt)
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
		_dy = _maxspeed * (_dty / (_dty + _acci)) * (dt);
	}
	else if (_dty < 0) {
		_dy = -_maxspeed * (_dty / (_dty - _acci)) * (dt);
	}
}

void Pawn::UpdatePawn()
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
	_2D_Point point = MyHitBox.ClampToMoveableArea();
	if ((_centre.x)!= point.x || (_centre.y != point.y)){
		_centre.x = point.x;
		_centre.y = point.y;
		_dx = 0; _dtx = 0;
		_dy = 0; _dty = 0;
	}
	_path.p2.x = _centre.x;
	_path.p2.y = _centre.y;
}

int Pawn::QuerySize()
{
	return _size;
}

void Pawn::collisionDetected(Pawn * collidingPawn)
{
	//OutputDebugString(L"Hit! \n");
	if(MyController->GetTarget() == collidingPawn)
	{
		OutputDebugString(L"Hit Target! \n");
		_destroy = true;
	}
}

_2D_Point Pawn::QueryPosition()
{
	return _centre;
}
