#pragma once
#include "PCharacter.h"
class PDefaultCharacter :
	public PCharacter
{
public:
	PDefaultCharacter(_2D_Point p);
	~PDefaultCharacter();

	void UpdatePawn();

	void MoveHorizontal(int direction, double dt);
	void MoveVertical(int direction, double dt);


	void CollisionDetected(class Pawn * collidingPawn);
	void TouchingSurface(class Terrain * terra, const bool floor);
	void TouchingMapBoundary(bool a, bool b, bool c);

protected:

	static const int _maxspeed;
	static const float _a1;//acceleration interval
};

