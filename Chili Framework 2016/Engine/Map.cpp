#include "Map.h"
#include "Graphics.h"



void Map::Draw(Graphics & gfx, _2D_Point campos)
{
	if (tData == nullptr) {

	}
	else {
		if (tData[0][0] == nullptr) {}
		else {
			for (int i = 0; i < HEIGHT / Terrain::SIZE; i++)
			{
				for (int k = 0; k < WIDTH / Terrain::SIZE; k++)
				{
					bool inScreenBounds = true;
					_2D_Point posNorm;
					int xPos = 0, yPos = 0;
					xPos = k * Terrain::SIZE;
					yPos = i * Terrain::SIZE;
					if ((xPos - campos.x) < 400 - (Terrain::SIZE / 2) && (xPos - campos.x) > -400 + (Terrain::SIZE / 2)) {
						posNorm.x = (xPos - campos.x) + 400;
					}
					else { inScreenBounds = false; }

					if ((yPos - campos.y) < 300 - (Terrain::SIZE / 2) && (yPos - campos.y) > -300 + (Terrain::SIZE / 2)) {
						posNorm.y = (yPos - campos.y) + 300;
					}
					else { inScreenBounds = false; }

					if (inScreenBounds) {
						gfx.DrawRectangle(posNorm.x, posNorm.y, Terrain::SIZE, Terrain::SIZE, tData[i][k]->colour);
					}
				}
			}
		}
	}
}

void Map::MakeTerrainBlock(const Terrain & tb, const int & x, const int & y)
{
	tData[y][x] = new Terrain(tb);
}

void Map::Clear()
{
	for (int i = 0; i < HEIGHT / Terrain::SIZE; i++) {
		delete[] tData[i];
	}
	delete[] tData;
}
