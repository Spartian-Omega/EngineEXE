#pragma once

#include "Graphics.h"
#include "Controller.h"
#include "Pawn.h"
#include "_2D_Vector.h"
#include "Widget.h"
#include "CollisionField.h"


#include "Colors.h"

class GameState
{

public:
	GameState();
	~GameState();


	static int const GMESZE = 50; // Amount of Pawns in the Game

	Pawn * _pwnArry[GMESZE] = { nullptr };
	Controller * _CtrlArry[GMESZE] = { nullptr };
	CollisionField *_CollisionField = nullptr;
};

struct GSData {

	Pawn * _pwnArry[GameState::GMESZE] = { nullptr };
	Controller * _CtrlArry[GameState::GMESZE] = { nullptr };
	CollisionField *_CollisionField = nullptr;

	void Clear() {
		for (int i = 0; i < GameState::GMESZE; i++) {
			if (_pwnArry[i] != nullptr) {
				delete _pwnArry[i];
				_pwnArry[i] = nullptr;
			}
		}
	}

	void operator = (const GameState & GS) {
		for (int i = 0; i < GameState::GMESZE; i++) {
			if (GS._pwnArry[i] != nullptr) {
				_pwnArry[i] = new Pawn(*GS._pwnArry[i]);
			}
		}
	}
};