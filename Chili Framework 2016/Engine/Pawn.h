#pragma once
#include <string>
#include <sstream>

#include "Map.h"

#include "Collision.h"
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
	virtual void CollisionDetected(class Pawn * collidingPawn);
	virtual void TouchingSurface(class Terrain * terra, const bool floor);
	virtual void TouchingMapBoundary(bool a, bool b, bool c);


		
public:
	bool _destroy; // Default = false , Set to true when deleting the pawn.
protected:

	std::wstring _debug_wstream;

	//Physical Properties
	_2D_Point _centre;
	Shape * _shape;
	Collision _collision;
};

