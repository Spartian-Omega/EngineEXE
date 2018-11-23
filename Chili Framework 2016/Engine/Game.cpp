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


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	_GameState()
{
	// Initialise Player
	_Player = new Pawn(400, 300, 20);
	_PlayerController = new APlayerController(_Player, wnd);
	_Player->AssignController(_PlayerController);
	_GameState._PawnArray[0] = _Player;
	_ControllerArray[0] = _PlayerController;
	//

	///test
	//_PawnArray[1] = new Pawn(500, 300, 10);
	//_ControllerArray[1] = new ANPCController(_PawnArray[1]);
	//_PawnArray[1]->AssignController(_ControllerArray[1]);
	//_ControllerArray[1]->SetTarget(_PawnArray[0]);
	///
	///swarmtest
	//for (int i = 1; i < 51; i++) {
	//	_PawnArray[i] = new Pawn(rand() % 500, rand() % 300, rand() % 20);
	//	_ControllerArray[i] = new ANPCController(_PawnArray[i]);
	//	_PawnArray[i]->AssignController(_ControllerArray[i]);
	//	_ControllerArray[i]->SetTarget(_PawnArray[0]);
	//}
	///

	// Initialise CollisionField
	_CollisionField = new CollisionField();
	//
	
	_GameState._r = 255; _GameState._g = 255; _GameState._b = 255;
	_frameInterval = 0;
	DRAW = true;
	WAIT = false;
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

	/// Test Spawner 2	
		for (int i = 1; i <= _GameState.GAMESIZE; i++) {
			if (_GameState._PawnArray[i] == NULL) {
				_GameState._PawnArray[i] = new Pawn(rand() % 800, rand() % 600, rand() % 10 + 4);
				_ControllerArray[i] = new ANPCController(_GameState._PawnArray[i]);
				_GameState._PawnArray[i]->AssignController(_ControllerArray[i]);
				_ControllerArray[i]->SetTarget(_GameState._PawnArray[0]);
			}
		}

	UpdateModel();

	/// Push Game State to Buffer
	PushGameState();
	///

	ComposeFrame(); // Currently does nothing
	_CollisionField->EmptyCollisionField();


	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	_frameInterval = elapsed_seconds.count();
	//
	//
	_debug_wstream = std::to_wstring(_frameInterval);
	OutputDebugString(L"Frame Interval = ");
	OutputDebugString(_debug_wstream.c_str());
	OutputDebugString(L"\n");
	//
}

void Game::UpdateModel()
{	
	//_PlayerController->ControllerGo(_frameInterval);
	for (int i = 0; i < _GameState.GAMESIZE; i++) {
		if (_GameState._PawnArray[i] != NULL) {
			if (_GameState._PawnArray[i]->_destroy) {
				delete _GameState._PawnArray[i];
				_GameState._PawnArray[i] = nullptr;
				delete _ControllerArray[i];
				_ControllerArray[i] = nullptr;
			}
		}
		if (_ControllerArray[i] != NULL) {
			_ControllerArray[i]->ControllerGo(_frameInterval);
		}
		/// Move below To drawing thread
		if (_GameState._PawnArray[i] != NULL) {			
			_GameState._pawnCentre[i] = _GameState._PawnArray[i]->QueryPosition();
			_GameState._pawnSize[i] = _GameState._PawnArray[i]->QuerySize();
			_CollisionField->UpdateCollisionField(_GameState._PawnArray[i]);
		}
		///
	}

}

void Game::PushGameState()
{
	for (int i = 0; i < GameState::GAMESIZE; i++) {
		Buffer._PawnArray[i] = _GameState._PawnArray[i];
		Buffer._pawnSize[i] = _GameState._pawnSize[i];
		Buffer._pawnCentre[i] = _GameState._pawnCentre[i];
	}
	Buffer._r = _GameState._r;
	Buffer._g = _GameState._g;
	Buffer._b = _GameState._b;
}

void Game::PushFrame()
{
	WAIT = true;
	gfx.BeginFrame();
	DrawCollisionField();

	for (int i = 1; i < Buffer.GAMESIZE; i++) {
		if (Buffer._PawnArray[i] != NULL) {
			DrawCrosshair(Buffer._pawnCentre[i].x, Buffer._pawnCentre[i].y, Buffer._pawnSize[i], 127, 0, 255);
		}
	}
	DrawBox(Buffer._pawnCentre[0].x, Buffer._pawnCentre[0].y, Buffer._pawnSize[0], Buffer._r, Buffer._g, Buffer._b);
	gfx.EndFrame();
	WAIT = false;
}

void Game::ComposeFrame()
{

}

void Game::DrawBox(int xcentre, int ycentre, int size, int r, int g, int b)
{
	for (int i = 0; i <= (size / 4); i++) {
		gfx.PutPixel((xcentre - (size / 2)) + i, (ycentre - (size / 2)), r, g, b);
		gfx.PutPixel((xcentre - (size / 2)) + i, (ycentre + (size / 2)), r, g, b);
										   
		gfx.PutPixel((xcentre + (size / 4)) + i, (ycentre - (size / 2)), r, g, b);
		gfx.PutPixel((xcentre + (size / 4)) + i, (ycentre + (size / 2)), r, g, b);
					  			 
		gfx.PutPixel((xcentre - (size / 2)), (ycentre - (size / 2)) + i, r, g, b);
		gfx.PutPixel((xcentre - (size / 2)) + size, (ycentre - (size / 2)) + i, r, g, b);
					  
		gfx.PutPixel((xcentre - (size / 2)), (ycentre + (size / 4)) + i, r, g, b);
		gfx.PutPixel((xcentre + (size / 2)), (ycentre + (size / 4)) + i, r, g, b);
	}
}

void Game::DrawCrosshair(int xcentre, int ycentre, int size, int r, int g, int b)
{
	for (int i = 0; i <= (size / 4); i++) {
		gfx.PutPixel(xcentre - (i + (size / 4)), ycentre, r, g, b);
		gfx.PutPixel(xcentre + (i + (size / 4)), ycentre, r, g, b);

		gfx.PutPixel(xcentre, ycentre - (i + (size / 4)), r, g, b);
		gfx.PutPixel(xcentre, ycentre + (i + (size / 4)), r, g, b);
	}
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

