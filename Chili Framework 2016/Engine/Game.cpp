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

#include "Game.h"
#include <chrono>

// Chilli Includes
#include "MainWindow.h"

// Custom Includes
#include "Widget.h"
#include "Button.h"
#include "Controller.h"
#include "APlayerController.h"
#include "ANPCController.h"
#include "Pawn.h"
#include "_2D_Vector.h"
#include "Menu.h"
#include "Match.h"
#include "CollisionField.h"


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{

	_cycleInterval = 0;
	gLatch = false;
	bLatch = false;

	_StgFlw.CStge = new Menu(wnd);
	_StgFlw.NStge = new Match(wnd);

	DRAW = true;
}

Game::~Game()
{
	DRAW = false;
	while(gLatch){}
}

void Game::Go()
{
	// ...
	auto start = std::chrono::system_clock::now();

	// Stage Swapping
	if (_StgFlw.CStge->NextLevel()) {
		_StgFlw.PStge = _StgFlw.CStge;
		_StgFlw.CStge = _StgFlw.NStge;
	}
	else {
		_StgFlw.CStge->StageGo(_cycleInterval);
	}
	//


	/// Push Game State to Buffer
	HOLD = true;
	if (!gLatch && bLatch) {
		PushGameState();
		PushUI();
		PushMap();
		bLatch = false;
	}
	else {
		bLatch = true;
	}
	HOLD = false;
	///

	// Game.Go() cycle time calculation and debug output.
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	_cycleInterval = elapsed_seconds.count();
	_debug_wstream = std::to_wstring(_cycleInterval);
	_debug_wstream = L"Cycle Interval = " + _debug_wstream + L"\n";
	OutputDebugString(_debug_wstream.c_str());
	// ...
}

void Game::PushUI()
{
	//
	_BUI = _StgFlw.CStge->GetUI();
	//
}

void Game::PushGameState()
{
	//
	_BST = _StgFlw.CStge->GetGameState();
	//
}

void Game::PushMap()
{
	//
	_BMP = _StgFlw.CStge->GetMap();
	//
}

void Game::PushFrame()
{
	gLatch = true;
	gfx.BeginFrame();

	// Get Camera Position
	_2D_Point camPos;
	if (_BST._pwnArry[0] != nullptr) {
		camPos = _BST._pwnArry[0]->QueryPosition();
	}
	//

	// Draw Map
	_BMP.Draw(gfx, camPos);
	//


////	_GameState.DrawCollisionField()->DrawField(wnd , gfx);

	// Draw Pawns
	for (int i = 0; i < GameState::GMESZE; i++) {
		if (_BST._pwnArry[i] != nullptr) {
			_BST._pwnArry[i]->Draw(gfx, camPos);
		}
	}
	//

	// Draw UI
	for (int i = 0; i < UserInterface::WAMNT; i++) {
		if (_BUI.DWidgets[i].IsVisible()) {
			_BUI.DWidgets[i].Draw(gfx);
		}
		if (_BUI.DButtons[i].IsVisible()) {
			_BUI.DButtons[i].Draw(gfx);
		}
	}
	//

	gfx.EndFrame();
	// Clear Buffer Memory
	_BUI.Clear();
	_BST.Clear();
	_BMP.Clear();
	//
	gLatch = false;
}

