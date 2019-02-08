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


	void collisionDetected(class Pawn * collidingPawn);

protected:

	static const int _maxspeed;
	static const float _a1;//acceleration interval
};

