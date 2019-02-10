#pragma once

#include <string>

#include "_2D_Vector.h"
#include "Colors.h"

class Graphics;

struct Terrain
{
	static const int SIZE = 10;

	std::wstring type;
	Color colour;
	int health;

	//Size is Currently {10 px * 10 px}

	Terrain(const std::wstring & t, const Color & c, const int & h) : type(t), colour(c), health(h) {}
	Terrain(const Terrain & terra) : type(terra.type), colour(terra.colour), health(terra.health) {}
};

// Defined Terrain Types
namespace TerraTypes
{
	static const Terrain MakeTerrain(const std::wstring & t, const Color & c, const int & h) {
		return Terrain(t, c, h);
	}
	static const Terrain Air = MakeTerrain(L"Air", Colors::Blue, 0);
	static const Terrain Grass = MakeTerrain(L"Grass", Colors::Green, 100);
	static const Terrain Stone = MakeTerrain(L"Stone", Colors::Gray, 200);
}


class Map
{
public:
	Map() : WIDTH(0), HEIGHT(0) { ; }
	Map(const int & w, const int & h) : WIDTH(w), HEIGHT(h) {
		if (HEIGHT != 0 && WIDTH != 0) {
			tData = new Terrain**[HEIGHT / Terrain::SIZE];
			for (int i = 0; i < HEIGHT / Terrain::SIZE; i++) {
				tData[i] = new Terrain*[WIDTH / Terrain::SIZE];
			}
		}
	}
	Map(const Map & m) : Map(m.WIDTH, m.HEIGHT)
	{
		if (HEIGHT != 0 && WIDTH != 0) {
			for (int i = 0; i < HEIGHT / Terrain::SIZE; i++) { for (int k = 0; k < WIDTH / Terrain::SIZE; k++) { tData[i][k] = m.tData[i][k]; } }
		}
	}
	~Map() {}

	int QueryWidth() const { return WIDTH; }
	int QueryHeight() const { return HEIGHT; }

	void Draw(Graphics & gfx, _2D_Point campos);
	void MakeTerrainBlock(const Terrain & tb, const int & x, const int & y);
	void Clear();

protected:
	Terrain *** tData = nullptr;
	int WIDTH;
	int HEIGHT;
};

// Defined Default Maps
namespace DefaultMaps
{
	static const Map MakeDefaultMap() {
		int width = 1000, height = 600;
		Map m(width, height);
		for (int i = 0; i < height / Terrain::SIZE; i++) {
			for (int k = 0; k < width / Terrain::SIZE; k++) {
				if (i > 40) {
					m.MakeTerrainBlock(TerraTypes::Stone, k, i);
				}
				else if (i > 37 && i <= 40) {
					m.MakeTerrainBlock(TerraTypes::Grass, k, i);
				}
				else {					
					m.MakeTerrainBlock(TerraTypes::Air, k, i);
				}
			}
		}
		return m;
	}
	static const Map DefaultMap = MakeDefaultMap();

	const _2D_Point ORIGIN = _2D_Point(0, 0); // Origin is 2D point situated at ( 0 , 0 )
}