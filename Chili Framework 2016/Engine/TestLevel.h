#pragma once
#include "Level.h"

class GameState;
class MainWindow;

class Pawn;
class APlayerController;


class TestLevel :
	public Level
{
public:
	TestLevel(GameState & g , MainWindow & wnd);
	~TestLevel();

	void LevelGo(double dt);

private:

	Pawn * _Player;

	APlayerController * _PlayerController;

};

