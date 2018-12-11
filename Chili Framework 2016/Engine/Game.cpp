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

	_cycleInterval = 0;
	DRAW = true;
	WAIT = false;

	_LevelPath.CurrentLevel = new Menu(_GameState);
	_LevelPath.NextLevel = new TestLevel(_GameState, wnd);

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


	_LevelPath.LevelPathGo();
	_LevelPath.CurrentLevel->LevelGo(_cycleInterval);





	UpdateWidget();

	/// Push Game State to Buffer
	PushGameState();

	///




	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;



	_cycleInterval = elapsed_seconds.count();
	//_debug_wstream = std::to_wstring(_cycleInterval);
	//_debug_wstream = L"Cycle Interval = " + _debug_wstream + L"\n";
	//OutputDebugString(_debug_wstream.c_str());
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
		GameState temp;
		for (int i = 0; i < GameState::GAMESIZE; i++) {
			temp._pawnArray[i] = _GameState._pawnArray[i];
			temp._pawnSizeH[i] = _GameState._pawnSizeH[i];
			temp._pawnSizeW[i] = _GameState._pawnSizeW[i];
			temp._pawnCentre[i] = _GameState._pawnCentre[i];
			temp._pawnColour[i] = _GameState._pawnColour[i];
			temp._widgetArray[i] = _GameState._widgetArray[i];
		}
		Buffer = temp;
		HOLD = false;
	}
}

void Game::PushFrame()
{
	WAIT = true;
	gfx.BeginFrame();
//	_GameState.DrawCollisionField()->DrawField(wnd , gfx);
	for (int i = 1; i < Buffer.GAMESIZE; i++) {
		if (Buffer._pawnArray[i] != NULL) {
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

