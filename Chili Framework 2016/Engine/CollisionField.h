#pragma once
#include "Pawn.h"
#include "Graphics.h"
#include "MainWindow.h"



class CollisionField
{
public:
	CollisionField(const int & w, const int & h);
	~CollisionField();

	void UpdateCollisionField(class Pawn * pawn);
	void EmptyCollisionField();

	void DrawField(class MainWindow & wnd, class Graphics & gfx);


private:
	int const WIDTH;
	int const HEIGHT;
	Pawn *** _CllArry;
	Pawn *** _oldArray;
};

