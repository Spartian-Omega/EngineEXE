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
	friend class Match;
	friend struct GSData;
public:
	GameState();
	~GameState();

protected:
	static int const GMESZE = 100; // Amount of Pawns in the Game

	Pawn * _pwnArry[GMESZE] = { nullptr };
	Controller * _CtrlArry[GMESZE] = { nullptr };
	CollisionField *_CollisionField;
};

struct GSData {

	Pawn * _pwnArry[GameState::GMESZE] = { nullptr };
	Controller * _CtrlArry[GameState::GMESZE] = { nullptr };
	CollisionField *_CollisionField;

	void operator = (const GameState & GS) {
		for (int i = 0; i < GameState::GMESZE; i++) {
			if (GS._pwnArry[i] != nullptr) {
				Pawn * nptr;
				*nptr = *GS._pwnArry[i];
				_pwnArry[i] = nptr;
			}
		}
	}
};