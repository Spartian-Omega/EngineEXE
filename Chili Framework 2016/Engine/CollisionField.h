#pragma once
#include "Pawn.h"
#include "Graphics.h"
#include "MainWindow.h"



class CollisionField
{
public:
	CollisionField();
	~CollisionField();

	void UpdateCollisionField(class Pawn * pawn);
	void EmptyCollisionField();

	void DrawField(class MainWindow & wnd, class Graphics & gfx);


private:
	Pawn * _pawnArray[600][800];
	Pawn * _oldArray[600][800];
};

