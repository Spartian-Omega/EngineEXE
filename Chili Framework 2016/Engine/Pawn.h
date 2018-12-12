#pragma once
#include "HitBox.h"
#include "Controller.h"
#include "_2D_Vector.h"
#include "Colors.h"
#include "Shape.h"
#include <string>
#include <sstream>

class Graphics;

class Pawn
{
public:
	Pawn(_2D_Point p, Shape * s);
	~Pawn();

	void Draw(Graphics & gfx);

	void AssignController(class Controller * controller);
	void MoveHorizontal(int direction, double dt);
	void MoveVertical(int direction, double dt);

	void SetColour(Color c) { _shape->SetColour(c); }

	void UpdatePawn();

	int QuerySizeH() { return _shape->QueryHeight(); }
	int QuerySizeW() { return _shape->QueryWidth(); }
	_2D_Point QueryPosition(){ return _centre; }
	Color QueryColour(){ return _shape->GetColour(); }

	void collisionDetected(class Pawn * collidingPawn);


	//Friction of the current surface;
	float _areaFriction;
	//

public:
	bool _destroy;

protected:

	std::wstring _debug_wstream;


	Controller * MyController;

	//Physical Properties
	_2D_Point _centre;
	Shape * _shape;
	HitBox _hbox;

	//Dynamic Properties
	double _dx, _dy;
	double _dtx, _dty;
	_2D_Vector _path;

	int _maxspeed;
	float _acci; //acceleration interval
};

