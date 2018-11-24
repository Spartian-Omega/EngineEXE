#pragma once
#include "HitBox.h"
#include "Controller.h"
#include "_2D_Vector.h"
#include "Colors.h"
#include <string>
#include <sstream>



class Pawn
{
public:
	Pawn(int x, int y, int size);
	~Pawn();

	void AssignController(class Controller * controller);
	void MoveHorizontal(int direction, double dt);
	void MoveVertical(int direction, double dt);

	void SetColour(class Color c);

	void UpdatePawn();
	int QuerySize();
	_2D_Point QueryPosition();
	Color QueryColour();

	void collisionDetected(class Pawn * collidingPawn);


	//Friction of the current surface;
	float _areaFriction;
	//

public:
	bool _destroy;

private:

	std::wstring _debug_wstream;

	HitBox MyHitBox;
	Controller * MyController;

	//Physical Properties
	_2D_Point _centre;
	int	  _size;
	Color _c;
	std::wstring _shape;

	//Dynamic Properties
	double _dx, _dy;
	double _dtx, _dty;
	_2D_Vector _path;

	int _maxspeed;
	float _acci; //acceleration interval
};

