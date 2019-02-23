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

	virtual void CollisionDetected(class Pawn * collidingPawn);
	

public:
	//Friction of the current surface;
	float _areaFriction;
	//

protected:

	bool _boundaryTop = true;
	bool _boundaryBottom = true;
	bool _boundaryLeft = true;
	bool _boundaryRight = true;

	Controller * MyController;

	//Dynamic Properties
	double _dx, _dy;
	double _dtx, _dty;
	_2D_Vector _path;

};

