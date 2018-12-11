#pragma once

#include "Map.h"


class Level
{
	friend struct LevelPath;
public:
	Level(class GameState & g);
	virtual ~Level();

	virtual void LevelGo(double dt);

protected:
	Map _map;
	GameState & _GameState;
	bool _nextLevel = false;

};


struct LevelPath
{
	Level * CurrentLevel = nullptr;
	Level * NextLevel = nullptr;

	void LevelPathGo() {
		if (CurrentLevel->_nextLevel) {
			delete CurrentLevel;
			CurrentLevel = NextLevel;
		}
	}
};

