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
	InitialiseMap();

	// Initialise Player
	InitialisePlayers();

	// Initialise CollisionField
	InitialiseCollisionField();
	
}


Match::~Match()
{
}

void Match::InitialiseMap()
{
	_Map = DefaultMaps::DefaultMap;
}

void Match::InitialisePlayers()
{
	_2D_Point locSpawn(DefaultMaps::ORIGIN.x + 50 , DefaultMaps::ORIGIN.y + 50);
	_Player = new PDefaultCharacter(locSpawn);
	_PlayerController = new APlayerController(_Player, _UI.QueryMainWindow());
	_Player->AssignController(_PlayerController);
	_State._pwnArry[0] = _Player;
	_State._CtrlArry[0] = _PlayerController;
}

void Match::InitialiseCollisionField()
{
	_State._CollisionField = new CollisionField(_Map.QueryWidth(), _Map.QueryHeight());
	_State._CollisionField->UpdateWTerrain(_Map.QueryTerrain());
}

void Match::StageGo(double dt)
{

/// Test Spawner
///*
//if (_PlayerController->ControlIsPressed()) {
//
//	for (int i = 1; i <= _State.GMESZE; i++) {
//		if (_State._pwnArry[i] == nullptr) {
//			_State._pwnArry[i] = new PDefaultCharacter(_2D_Point(rand() % (int(DefaultMaps::ORIGIN.x) + _Map.QueryWidth()), rand() % (int(DefaultMaps::ORIGIN.y) + _Map.QueryHeight())));
//			PCharacter * pd = static_cast<PCharacter*>(_State._pwnArry[i]);
//			_State._CtrlArry[i] = new ANPCController(pd);
//			pd->AssignController(_State._CtrlArry[i]);
//			_State._CtrlArry[i]->SetTarget(_Player);
//		}
//	}
//}
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
		if (_State._pwnArry[i] != nullptr) {
			_State._CollisionField->UpdateWPawn(_State._pwnArry[i]);
		}
	}


	_State._CollisionField->EmptyCollisionField();
}
