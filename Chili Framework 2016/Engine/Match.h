#pragma once
#include "Stage.h"
#include "GameState.h"
#include "APlayerController.h"



class Match :
	public Stage
{
public:
	Match(MainWindow & wnd);
	~Match();

	void StageGo(double dt);

private:

	GameState _State;
	Pawn * _Player;
	APlayerController * _PlayerController;

};

