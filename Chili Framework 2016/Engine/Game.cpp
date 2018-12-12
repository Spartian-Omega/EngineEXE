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
	gfx(wnd)
{

	_cycleInterval = 0;
	WAIT = false;

	_StgFlw.CStge = new Menu(wnd);
	_StgFlw.NStge = new Match(wnd);

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

	_StgFlw.StagePathGo();
	_StgFlw.CStge->StageGo(_cycleInterval);

	/// Push Game State to Buffer

		HOLD = true;
		PushGameState();
		PushUI();
		HOLD = false;
		///

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	_cycleInterval = elapsed_seconds.count();
	//_debug_wstream = std::to_wstring(_cycleInterval);
	//_debug_wstream = L"Cycle Interval = " + _debug_wstream + L"\n";
	//OutputDebugString(_debug_wstream.c_str());
	DRAW = true;
}

void Game::PushUI()
{
	//
	_BUI = _StgFlw.CStge->GetUI();
	//
}

void Game::PushGameState()
{



}

void Game::PushFrame()
{
	WAIT = true;
	gfx.BeginFrame();
////	_GameState.DrawCollisionField()->DrawField(wnd , gfx);
//	for (int i = 1; i < Buffer.GAMESIZE; i++) {
//		if (Buffer._pwnArry[i] != nullptr) {
//			gfx.DrawRectangle(Buffer._pawnCentre[i].x, Buffer._pawnCentre[i].y, Buffer._pawnSizeW[i], Buffer._pawnSizeH[i],  Buffer._pawnColour[i]);
//		}
//	}
//	gfx.DrawCBox(Buffer._pawnCentre[0].x, Buffer._pawnCentre[0].y, Buffer._pawnSizeW[0], Buffer._pawnColour[0]);
//
	//Draw UI

	for (int i = 0; i < UserInterface::WAMNT; i++) {
		if (_BUI.DWidgets[i].IsVisible()) {
			_BUI.DWidgets[i].Draw(gfx);
		}
		if (_BUI.DButtons[i].IsVisible()) {
			_BUI.DButtons[i].Draw(gfx);
		}
	}

	gfx.EndFrame();
	WAIT = false;
}

