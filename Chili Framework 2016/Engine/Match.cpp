#include "Match.h"

#include "Controller.h"
#include "MainWindow.h"
#include "ANPCController.h"
#include "PDefaultCharacter.h"
#include "_2D_Vector.h"
#include "CollisionField.h"
#include "Square.h"



Match::Match(MainWindow & wnd) : Stage(wnd)
{
	// Initialise Map
	_Map = DefaultMaps::DefaultMap;

	// Initialise Player
	_Player = new PDefaultCharacter(DefaultMaps::ORIGIN);
	_PlayerController = new APlayerController(_Player, wnd);
	_Player->AssignController(_PlayerController);
	_State._pwnArry[0] = _Player;
	_State._CtrlArry[0] = _PlayerController;
	

	// Initialise CollisionField
	_State._CollisionField = new CollisionField(_Map.QueryWidth() , _Map.QueryHeight());
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
		if (_State._pwnArry[i] == nullptr) {
			_State._pwnArry[i] = new PDefaultCharacter(_2D_Point(rand() % (int(DefaultMaps::ORIGIN.x) + 100), rand() % (int(DefaultMaps::ORIGIN.y) + 100)));
			PCharacter * pd = static_cast<PCharacter*>(_State._pwnArry[i]);
			_State._CtrlArry[i] = new ANPCController(pd);
			pd->AssignController(_State._CtrlArry[i]);
			_State._CtrlArry[i]->SetTarget(_Player);
		}
	}
}
///
//*/
	
	for (int i = 0; i < _State.GMESZE; i++) {
		if (_State._pwnArry[i] != nullptr) {
			if (_State._pwnArry[i]->_destroy) {
				delete _State._pwnArry[i];
				_State._pwnArry[i] = nullptr;
				delete _State._CtrlArry[i];
				_State._CtrlArry[i] = nullptr;
			}
		}
		if (_State._CtrlArry[i] != nullptr) {
			_State._CtrlArry[i]->ControllerGo(dt);
		}
		/// Move below To drawing thread
		if (_State._pwnArry[i] != nullptr) {
			_State._CollisionField->UpdateCollisionField(_State._pwnArry[i]);
		}
		///
	}


	_State._CollisionField->EmptyCollisionField();
}
