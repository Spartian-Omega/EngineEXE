#pragma once
#include "Pawn.h"
#include "Controller.h"

class PDynamic :
	public Pawn
{
public:
	PDynamic(_2D_Point p, Shape * s);
	~PDynamic();

	void SetColour(Color c) { _shape->SetColour(c); }
	void AssignController(class Controller * controller);


	virtual void UpdatePawn();

	virtual	void MoveHorizontal(int direction, double dt);
	virtual	void MoveVertical(int direction, double dt);

	virtual void collisionDetected(class Pawn * collidingPawn);
	

public:
	//Friction of the current surface;
	float _areaFriction;
	//

protected:

	Controller * MyController;

	//Dynamic Properties
	double _dx, _dy;
	double _dtx, _dty;
	_2D_Vector _path;

};

