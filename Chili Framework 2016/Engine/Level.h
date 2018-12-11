#pragma once

#include "Map.h"

class Level
{
public:
	Level(class GameState & g);
	~Level();

	virtual void LevelGo(double dt);

protected:
	Map _map;
	GameState & _GameState;

};

