#pragma once

#include "Graphics.h"
#include "Controller.h"
#include "Pawn.h"
#include "_2D_Vector.h"
#include "Menu.h"
#include "Widget.h"
#include "CollisionField.h"


#include "Colors.h"

class GameState
{
	friend class Game;
	friend class Menu;
	friend class TestLevel;
public:
	GameState();
	~GameState();

	void IsHost(bool ishost) { isHost = ishost; }
	void SetHost() {}

protected:
	static int const GAMESIZE = 100; // Amount of Pawns in the Game

	bool isHost = true;


	Pawn * _pawnArray[GAMESIZE] = { nullptr };
	int _pawnSizeW[GAMESIZE];
	int _pawnSizeH[GAMESIZE];
	_2D_Point _pawnCentre[GAMESIZE];
	Color _pawnColour[GAMESIZE];

	Controller * _ControllerArray[GAMESIZE] = { nullptr };

	CollisionField *_CollisionField;

	Widget * _widgetArray[100] = { nullptr };
};

