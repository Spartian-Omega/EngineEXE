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
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Controller.h"

#include "GameState.h"

#include "APlayerController.h"
#include "ANPCController.h"
#include "Pawn.h"
#include "_2D_Vector.h"
#include "CollisionField.h"



class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	~Game();
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void UpdateModel();
	/// Super Special Function
	void PushGameState();
public:
	void PushFrame();
	///
private:
	/********************************/
	/*  User Functions              */

	bool CheckForOverlap(const int xcentre1, const int ycentre1, const int size1, const int xcentre2, const int ycentre2, const int size2);
	bool CheckForScreenBoundaryTouch(const int scentre, const int size, const int sboundary);
	void DrawCollisionField();
	/********************************/
public:
	bool DRAW;
	bool WAIT;
	bool HOLD;
private:
	MainWindow& wnd;
	Graphics gfx;

	Pawn * _Player;
	CollisionField *_CollisionField;

	double _cycleInterval;
	std::wstring _debug_wstream;

	GameState _GameState;
	GameState Buffer;
protected:
	/********************************/
	/*  User Variables              */

	Controller * _PlayerController;
	Controller * _ControllerArray[GameState::GAMESIZE];

	/********************************/
};