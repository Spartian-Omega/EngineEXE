#pragma once
#include "Pawn.h"
#include "Map.h"

class CollisionField
{
public:
	CollisionField(const int & w, const int & h);
	~CollisionField();

	void UpdateWTerrain(Terrain *** tdata);
	void UpdateWPawn(Pawn * pawn);

	void EmptyCollisionField();
	void DrawField(class MainWindow & wnd, class Graphics & gfx);


private:
	int const WIDTH;
	int const HEIGHT;
	Pawn *** _CllArry = nullptr;
	Pawn *** _oldArray = nullptr;
	Terrain *** tData = nullptr;
};

