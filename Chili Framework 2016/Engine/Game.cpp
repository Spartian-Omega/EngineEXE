/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/

#include <chrono>
#include "MainWindow.h"
#include "Game.h"
#include "Widget.h"
#include "Button.h"


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	_GameState()
{
	// Initialise Player
	_Player = new Pawn(400, 300, 20, 20);
	_PlayerController = new APlayerController(_Player, wnd);
	_Player->AssignController(_PlayerController);
	_GameState._pawnArray[0] = _Player;
	_ControllerArray[0] = _PlayerController;
	//

	// Initialise CollisionField
	_CollisionField = new CollisionField();
	//
	
	_GameState._pawnColour[0] = Color(255, 255, 255);
	_cycleInterval = 0;
	DRAW = true;
	WAIT = false;

	_CurrentLevel = new Menu(_GameState);

}

Game::~Game()
{
	DRAW = false;
	while(WAIT){}
}

void Game::Go()
{
	//
	auto start = std::chrono::system_clock::now();

	_CurrentLevel->LevelGo(_cycleInterval);

	/// Test Spawner
	/*
	if (wnd.kbd.KeyIsPressed(VK_CONTROL)) {

		for (int i = 1; i <= _GameState.GAMESIZE; i++) {
			if (_GameState._pawnArray[i] == NULL) {
				_GameState._pawnArray[i] = new Pawn(rand() % 800, rand() % 600, rand() % 20 + 4, rand() % 20 + 4);
				_ControllerArray[i] = new ANPCController(_GameState._pawnArray[i]);
				_GameState._pawnArray[i]->AssignController(_ControllerArray[i]);
				_ControllerArray[i]->SetTarget(_GameState._pawnArray[0]);
			}
		}

	}
	///
	*/

	UpdateModel();

	UpdateWidget();

	/// Push Game State to Buffer
	PushGameState();

	///

	_CollisionField->EmptyCollisionField();



	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;



	_cycleInterval = elapsed_seconds.count();
	//_debug_wstream = std::to_wstring(_cycleInterval);
	//_debug_wstream = L"Cycle Interval = " + _debug_wstream + L"\n";
	//OutputDebugString(_debug_wstream.c_str());
}

void Game::UpdateModel()
{	
	//_PlayerController->ControllerGo(_frameInterval);
	for (int i = 0; i < _GameState.GAMESIZE; i++) {
		if (_GameState._pawnArray[i] != NULL) {
			if (_GameState._pawnArray[i]->_destroy) {
				delete _GameState._pawnArray[i];
				_GameState._pawnArray[i] = nullptr;
				delete _ControllerArray[i];
				_ControllerArray[i] = nullptr;
			}
		}
		if (_ControllerArray[i] != NULL) {
			_ControllerArray[i]->ControllerGo(_cycleInterval);
		}
		/// Move below To drawing thread
		if (_GameState._pawnArray[i] != NULL) {			
			_GameState._pawnCentre[i] = _GameState._pawnArray[i]->QueryPosition();
			_GameState._pawnSizeH[i] = _GameState._pawnArray[i]->QuerySizeH();
			_GameState._pawnSizeW[i] = _GameState._pawnArray[i]->QuerySizeW();
			_GameState._pawnColour[i] = _GameState._pawnArray[i]->QueryColour();
			_CollisionField->UpdateCollisionField(_GameState._pawnArray[i]);
		}
		///
	}

}

void Game::UpdateWidget()
{
	_2D_Point mousePosition(0, 0);
	if (wnd.mouse.LeftIsPressed()) {
		mousePosition.x = wnd.mouse.GetPosX();
		mousePosition.y = wnd.mouse.GetPosY();

		std::wstring mx , my;
		mx = std::to_wstring(mousePosition.x);
		my = std::to_wstring(mousePosition.y);
		_debug_wstream = L"Mouse x (" + mx + L") Mouse y (" + my + L")\n";
		OutputDebugString(_debug_wstream.c_str());
	//
		for (int i = 0; i < 100; i++) {		
			Button *bptr = dynamic_cast<Button*>(_GameState._widgetArray[i]);
			if (bptr != NULL) {
				bptr->QueryHit(mousePosition);
			}
		}
	}
	//

	//
}

void Game::PushGameState()
{
	if (WAIT) {
		HOLD = true;
		for (int i = 0; i < GameState::GAMESIZE; i++) {
			Buffer._pawnArray[i] = _GameState._pawnArray[i];
			Buffer._pawnSizeH[i] = _GameState._pawnSizeH[i];
			Buffer._pawnSizeW[i] = _GameState._pawnSizeW[i];
			Buffer._pawnCentre[i] = _GameState._pawnCentre[i];
			Buffer._pawnColour[i] = _GameState._pawnColour[i];

			Buffer._widgetArray[i] = _GameState._widgetArray[i];
		}
		HOLD = false;
	}
}

void Game::PushFrame()
{
	WAIT = true;
	gfx.BeginFrame();
//	DrawCollisionField();
	for (int i = 1; i < Buffer.GAMESIZE; i++) {
		if (Buffer._pawnArray[i] != NULL) {
			//if (Buffer._pawnSizeW[i] < Buffer._pawnSizeH[i]) {
			//	gfx.DrawCrosshair(Buffer._pawnCentre[i].x, Buffer._pawnCentre[i].y, Buffer._pawnSizeH[i], Buffer._pawnColour[i]);
			//}
			//else {
			//	gfx.DrawCrosshair(Buffer._pawnCentre[i].x, Buffer._pawnCentre[i].y, Buffer._pawnSizeW[i], Buffer._pawnColour[i]);
			//}
			gfx.DrawRectangle(Buffer._pawnCentre[i].x, Buffer._pawnCentre[i].y, Buffer._pawnSizeW[i], Buffer._pawnSizeH[i],  Buffer._pawnColour[i]);
		}
	}
	gfx.DrawCBox(Buffer._pawnCentre[0].x, Buffer._pawnCentre[0].y, Buffer._pawnSizeW[0], Buffer._pawnColour[0]);

	for (int i = 0; i < 100; i++) {
		if (Buffer._widgetArray[i] != NULL) {
			Buffer._widgetArray[i]->Draw(gfx);
		}
	}

	gfx.EndFrame();
	WAIT = false;
}







bool Game::CheckForOverlap(int xcentre1, int ycentre1, int size1, int xcentre2, int ycentre2, int size2)
{
	return ((xcentre1 + (size1 / 2)) >= (xcentre2 - (size2 / 2)) &&
			(xcentre1 - (size1 / 2)) <= (xcentre2 + (size2 / 2)) &&
			(ycentre1 + (size1 / 2)) >= (ycentre2 - (size2 / 2)) &&
			(ycentre1 - (size1 / 2)) <= (ycentre2 + (size2 / 2)));
}

bool Game::CheckForScreenBoundaryTouch(int scentre, int size, int sboundary)
{
	return ((scentre - (size / 2)) > 0 && (scentre + (size / 2)) < sboundary);
}

void Game::DrawCollisionField()
{
	_CollisionField->DrawField(wnd , gfx);
}

