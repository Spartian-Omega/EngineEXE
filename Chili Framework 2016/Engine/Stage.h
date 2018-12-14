#pragma once


#include "GameState.h"
#include "UserInterface.h"
#include "Map.h"

class MainWindow;


class Stage
{
public:
	Stage(MainWindow & wnd);
	virtual ~Stage();

	virtual void StageGo(double dt);
	virtual void UpdateUI(double dt);

	bool NextLevel() { return _STAGEEND; }

	UserInterface GetUI() { return _UI; }
	GameState GetGameState() { return _State; }
	Map GetMap() { return _Map; }

protected:

	bool _STAGEEND = false;
	UserInterface _UI;
	GameState _State;
	Map _Map;

};


struct StagePath
{
	Stage * CStge;
	Stage * NStge;
	Stage * PStge;
};

