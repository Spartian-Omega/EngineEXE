#pragma once

#include "Graphics.h"
#include "Controller.h"
#include "Pawn.h"
#include "_2D_Vector.h"

class GameState
{
	friend class Game;
public:
	GameState();
	~GameState();
protected:
	static int const GAMESIZE = 100; // Amount of Pawns in the Game
	Pawn * _PawnArray[GAMESIZE];
	int _pawnSize[GAMESIZE];
	_2D_Point _pawnCentre[GAMESIZE];
	int _r, _g, _b;
};

