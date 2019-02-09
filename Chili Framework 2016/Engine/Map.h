#pragma once

#include <string>

#include "_2D_Vector.h"
#include "Colors.h"

struct Terrain;
class Graphics;

class Map
{
public:
	Map();
	Map(const Map & m)
	{
		for (int i = 0; i < 60; i++) {	for (int k = 0; k < 80; k++){ tData[i][k] = m.tData[i][k]; }}
	}
	~Map();
	void Draw(Graphics & gfx, _2D_Point campos);
	void MakeTerrainBlock(const Terrain tb, const int & x, const int & y);

protected:
	Terrain * tData[60][80] = { nullptr };
};

struct Terrain
{
	static const int SIZE = 10;

	std::wstring type;
	Color colour;
	int health;

	//Size is Currently {10 px * 10 px}

	Terrain(const std::wstring t, const Color c, const int h) : type(t), colour(c), health(h) {}
	Terrain(const Terrain & terra) : type(terra.type), colour(terra.colour), health(terra.health) {}
};

// Defined Terrain Types
namespace TerraTypes
{
	static const Terrain MakeTerrain(const std::wstring t, const Color c,const int h) {
		return Terrain(t, c, h);
	}
	static const Terrain Air	= MakeTerrain(L"Air", Colors::Blue, 0);
	static const Terrain Grass	= MakeTerrain(L"Grass", Colors::Green, 100);
	static const Terrain Stone	= MakeTerrain(L"Stone", Colors::Gray, 200);
}

// Defined Default Maps
namespace DefaultMaps
{
	static const Map MakeDefaultMap() {
		Map m;
		for (int i = 0; i < 60; i++) {
			for (int k = 0; k < 80; k++) {
				if (i > 20) {
					m.MakeTerrainBlock(TerraTypes::Air, k, i);
				}
				else if (i > 17 && i <= 20) {
					m.MakeTerrainBlock(TerraTypes::Grass, k, i);
				}
				else {
					m.MakeTerrainBlock(TerraTypes::Stone, k, i);
				}
			}
		}
		return m;
	}
	static const Map DefaultMap = MakeDefaultMap();

	const _2D_Point ORIGIN = _2D_Point(0, 0); // Origin is 2D point situated at ( 0 , 0 )
}