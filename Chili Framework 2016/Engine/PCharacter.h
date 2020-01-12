#pragma once
#include "PDynamic.h"
class PCharacter :
	public PDynamic
{
public:
	PCharacter(_2D_Point p, Shape * s);
	~PCharacter();

	void UpdatePawn();

	void MoveHorizontal(int direction, double dt);
	void MoveVertical(int direction, double dt);


	void CollisionDetected(class Pawn * collidingPawn);


protected:
	bool _OnSurface = true;
	bool _OnCeil = true;
};

