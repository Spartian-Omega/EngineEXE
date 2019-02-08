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

	void Draw(Graphics & gfx);
	int QuerySizeH() { return _shape->QueryHeight(); }
	int QuerySizeW() { return _shape->QueryWidth(); }
	_2D_Point QueryPosition() { return _centre; }
	Color QueryColour() { return _shape->GetColour(); }
	

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

