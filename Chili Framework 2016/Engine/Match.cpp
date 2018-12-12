#include "Match.h"

#include "Controller.h"
#include "MainWindow.h"
#include "ANPCController.h"
#include "Pawn.h"
#include "_2D_Vector.h"
#include "CollisionField.h"




Match::Match(MainWindow & wnd) : Stage(wnd)
{
	// Initialise Player
	_Player = new Pawn(400, 300, 20, 20);
	_PlayerController = new APlayerController(_Player, wnd);
	_Player->AssignController(_PlayerController);
	_State._pwnArry[0] = _Player;
	_State._CtrlArry[0] = _PlayerController;
	//

	// Initialise CollisionField
	_State._CollisionField = new CollisionField();
	//
}


Match::~Match()
{
}

void Match::StageGo(double dt)
{

	/// Test Spawner
///*
if (_PlayerController->ControlIsPressed()) {

	for (int i = 1; i <= _State.GMESZE; i++) {
		if (_State._pwnArry[i] == NULL) {
			_State._pwnArry[i] = new Pawn(rand() % 800, rand() % 600, rand() % 20 + 4, rand() % 20 + 4);
			_State._CtrlArry[i] = new ANPCController(_State._pwnArry[i]);
			_State._pwnArry[i]->AssignController(_State._CtrlArry[i]);
			_State._CtrlArry[i]->SetTarget(_State._pwnArry[0]);
		}
	}
}
///
//*/
	
	//_PlayerController->ControllerGo(_frameInterval);
	for (int i = 0; i < _State.GMESZE; i++) {
		if (_State._pwnArry[i] != NULL) {
			if (_State._pwnArry[i]->_destroy) {
				delete _State._pwnArry[i];
				_State._pwnArry[i] = nullptr;
				delete _State._CtrlArry[i];
				_State._CtrlArry[i] = nullptr;
			}
		}
		if (_State._CtrlArry[i] != NULL) {
			_State._CtrlArry[i]->ControllerGo(dt);
		}
		/// Move below To drawing thread
		if (_State._pwnArry[i] != NULL) {
			_State._CollisionField->UpdateCollisionField(_State._pwnArry[i]);
		}
		///
	}


	_State._CollisionField->EmptyCollisionField();
}
