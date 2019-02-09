#pragma once
#include <string>
#include <sstream>

#include "HitBox.h"
#include "_2D_Vector.h"
#include "Shape.h"



class Graphics;

class Pawn
{
public:
	Pawn(_2D_Point p, Shape * s);
	~Pawn();

	const void Draw(Graphics & gfx, _2D_Point & campos);

	const int QuerySizeH() { return _shape->QueryHeight(); }
	const int QuerySizeW() { return _shape->QueryWidth(); }
	const _2D_Point QueryPosition() { return _centre; }
	const Color QueryColour() { return _shape->GetColour(); }
	

	virtual void UpdatePawn();
	virtual void collisionDetected(class Pawn * collidingPawn);
	


		
public:
	bool _destroy; // Default = false , Set to true when deleting the pawn.
protected:

	std::wstring _debug_wstream;

	//Physical Properties
	_2D_Point _centre;
	Shape * _shape;
	HitBox _hbox;
};

