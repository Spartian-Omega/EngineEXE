#include "TestLevel.h"

#include "Controller.h"

#include "GameState.h"

#include "APlayerController.h"
#include "ANPCController.h"
#include "Pawn.h"
#include "_2D_Vector.h"
#include "CollisionField.h"




TestLevel::TestLevel(GameState & g, MainWindow & wnd) : Level(g)
{
	// Initialise Player
	_Player = new Pawn(400, 300, 20, 20);
	_PlayerController = new APlayerController(_Player, wnd);
	_Player->AssignController(_PlayerController);
	_GameState._pawnArray[0] = _Player;
	_GameState._ControllerArray[0] = _PlayerController;
	//

	// Initialise CollisionField
	_GameState._CollisionField = new CollisionField();
	//
	_GameState._pawnColour[0] = Color(255, 255, 255);
}


TestLevel::~TestLevel()
{
}

void TestLevel::LevelGo(double dt)
{

	/// Test Spawner
///*
if (_PlayerController->ControlIsPressed()) {

	for (int i = 1; i <= _GameState.GAMESIZE; i++) {
		if (_GameState._pawnArray[i] == NULL) {
			_GameState._pawnArray[i] = new Pawn(rand() % 800, rand() % 600, rand() % 20 + 4, rand() % 20 + 4);
			_GameState._ControllerArray[i] = new ANPCController(_GameState._pawnArray[i]);
			_GameState._pawnArray[i]->AssignController(_GameState._ControllerArray[i]);
			_GameState._ControllerArray[i]->SetTarget(_GameState._pawnArray[0]);
		}
	}
}
///
//*/
	
	//_PlayerController->ControllerGo(_frameInterval);
	for (int i = 0; i < _GameState.GAMESIZE; i++) {
		if (_GameState._pawnArray[i] != NULL) {
			if (_GameState._pawnArray[i]->_destroy) {
				delete _GameState._pawnArray[i];
				_GameState._pawnArray[i] = nullptr;
				delete _GameState._ControllerArray[i];
				_GameState._ControllerArray[i] = nullptr;
			}
		}
		if (_GameState._ControllerArray[i] != NULL) {
			_GameState._ControllerArray[i]->ControllerGo(dt);
		}
		/// Move below To drawing thread
		if (_GameState._pawnArray[i] != NULL) {
			_GameState._pawnCentre[i] = _GameState._pawnArray[i]->QueryPosition();
			_GameState._pawnSizeH[i] = _GameState._pawnArray[i]->QuerySizeH();
			_GameState._pawnSizeW[i] = _GameState._pawnArray[i]->QuerySizeW();
			_GameState._pawnColour[i] = _GameState._pawnArray[i]->QueryColour();
			_GameState._CollisionField->UpdateCollisionField(_GameState._pawnArray[i]);
		}
		///
	}


	_GameState._CollisionField->EmptyCollisionField();


}
