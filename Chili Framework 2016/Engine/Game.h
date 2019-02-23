/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include <string>
#include <sstream>

// Chilli includes
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

// Custom includes
#include "GameState.h"
#include "UserInterface.h"
#include "Stage.h"



class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	~Game();
	Game& operator=(const Game&) = delete;
	void Go();
public:
	void PushFrame();
	///
private:
	/********************************/
	/*  User Functions              */
	/// Super Special Function
	void PushGameState();
	void PushUI();
	void PushMap();

	/********************************/
public:
	bool DRAW;		// While true the game will be drawn by the Graphics thread.
	bool HOLD;		// While true the game can not be drawn by the Graphics thread.
	bool gLatch;	// Graphics Drawing Latch , prevents a buffer write while the graphics thread is processing.
	bool bLatch;	// Push to Buffer Latch , allows a buffer write after the main thread makes a failed attempt to write. Also acts as a secondary HOLD.
private:
	MainWindow& wnd;
	Graphics gfx;

	double _cycleInterval;
	std::wstring _debug_wstream;

	GSData _BST; // Buffer GameState
	UIData _BUI; // Buffer UI
	Map	   _BMP; // Buffer Map

	StagePath _StgFlw;

protected:
	/********************************/
	/*  User Variables              */

	/********************************/
};