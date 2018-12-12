#pragma once
#include "Stage.h"
#include "APlayerController.h"



class Match :
	public Stage
{
public:
	Match(MainWindow & wnd);
	~Match();

	void StageGo(double dt);

private:


	Pawn * _Player;
	APlayerController * _PlayerController;

};

