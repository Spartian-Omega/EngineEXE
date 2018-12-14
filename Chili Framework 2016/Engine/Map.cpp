#include "Map.h"
#include "Graphics.h"



Map::Map()
{
}

Map::~Map()
{
}

void Map::Draw(Graphics & gfx)
{
	if (tData[0][0] == nullptr) {}
	else {
		for (int i = 0; i < 60; i++)
		{
			for (int k = 0; k < 80; k++)
			{
				int xPos = 0, yPos = 0;
				xPos = 5 + k * Terrain::SIZE;
				yPos = 595 - i * Terrain::SIZE;
				gfx.DrawRectangle( xPos, yPos, Terrain::SIZE, Terrain::SIZE, tData[i][k]->colour);
			}
		}
	}
}

void Map::MakeTerrainBlock(const Terrain tb, const int & x, const int & y)
{
	tData[y][x] = new Terrain(tb);
}
