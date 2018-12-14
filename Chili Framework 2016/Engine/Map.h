#pragma once

#include <string>

struct Terrain
{
	std::wstring type;
	int health;
	
	//Size is Currently {10 px * 10 px}
};

class Map
{
public:
	Map();
	~Map();

	void Draw(class Graphics & gfx);

protected:

	Terrain * terra[60][80] = { nullptr };

};

