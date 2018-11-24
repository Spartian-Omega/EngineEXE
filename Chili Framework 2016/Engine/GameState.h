#pragma once

#include "Graphics.h"
#include "Controller.h"
#include "Pawn.h"
#include "_2D_Vector.h"
#include "Colors.h"

class GameState
{
	friend class Game;
public:
	GameState();
	~GameState();
protected:
	static int const GAMESIZE = 1000; // Amount of Pawns in the Game
	Pawn * _pawnArray[GAMESIZE];
	int _pawnSize[GAMESIZE];
	_2D_Point _pawnCentre[GAMESIZE];
	Color _pawnColour[GAMESIZE];
};

