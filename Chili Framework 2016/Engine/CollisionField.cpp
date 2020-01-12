#include "CollisionField.h"

#include "Graphics.h"
#include "MainWindow.h"

#include "_2D_Vector.h"
#include "PDefaultCharacter.h"

CollisionField::CollisionField(const int & w, const int & h) : WIDTH(w) , HEIGHT(h)
{
	if (HEIGHT != 0 && WIDTH != 0) {
		_CllArry = new Pawn**[HEIGHT];
		_oldArray = new Pawn**[HEIGHT];
		for (int i = 0; i < HEIGHT; i++) {
			_CllArry[i] = new Pawn*[WIDTH];
			_oldArray[i] = new Pawn*[WIDTH];
		}
		tData = new Terrain**[HEIGHT / Terrain::SIZE];
		for (int i = 0; i < HEIGHT / Terrain::SIZE; i++) {
			tData[i] = new Terrain*[WIDTH / Terrain::SIZE];
		}
	}
}


CollisionField::~CollisionField()
{
}

void CollisionField::UpdateWTerrain(Terrain *** tdata)
{
	tData = tdata;
}

void CollisionField::UpdateWPawn(Pawn * pawn)
{
	_2D_Point pp = pawn->QueryPosition();
	int psh = pawn->QuerySizeH();
	int psw = pawn->QuerySizeW();
	double ppx = (int)pp.x;
	double ppy = (int)pp.y;
	
	int edgeTop = floor(ppy - psh / 2);
	int edgeBottom = ceil(ppy + psh / 2);
	int edgeLeft = ppx - psw / 2;
	int edgeRight = ppx + psw / 2;

	bool bT = false;
	bool bB = false;
	bool bL = false;
	bool bR = false;

	if (edgeTop <= 0) {
		pawn->TouchingMapBoundary(1, 0, 1);
		bT = true;
	}
	else	{
		pawn->TouchingMapBoundary(1, 0, 0);
	}
	if (edgeBottom >= HEIGHT) {
		pawn->TouchingMapBoundary(1, 1, 1);
		bB = true;
	}
	else	{
		pawn->TouchingMapBoundary(1, 1, 0);
	}
	if (edgeLeft <= 0) {
		pawn->TouchingMapBoundary(0, 1, 1);
		bL = true;
	}
	else	{
		pawn->TouchingMapBoundary(0, 1, 0);
	}
	if (edgeRight >= WIDTH) {
		pawn->TouchingMapBoundary(0, 0, 1);
		bR = true;
	}
	else	{
		pawn->TouchingMapBoundary(0, 0, 0);
	}
	
	/// Top and Bottom Edge Detection
	for (int i = 0; i <= psw; i++) {
		if (_CllArry[edgeTop][edgeLeft + i + 1] != nullptr) {
			pawn->CollisionDetected(_CllArry[edgeTop][edgeLeft + i + 1]);
		}
		else {
			_CllArry[edgeTop][edgeLeft + i + 1] = pawn;
		}
		if (_CllArry[edgeBottom][edgeRight - i - 1] != nullptr) {
			pawn->CollisionDetected(_CllArry[edgeBottom][edgeRight - i - 1]);
		}
		else {
			_CllArry[edgeBottom][edgeRight - i - 1] = pawn;
		}
		//...
		if (* tData[int(ceil(edgeTop / Terrain::SIZE))][int(round((edgeLeft + i) / Terrain::SIZE))] == TerraTypes::Air) {
			pawn->TouchingSurface(nullptr, 1);
		}
		else {
			pawn->TouchingSurface(tData[int(ceil(edgeTop / Terrain::SIZE))][int(round((edgeLeft + i) / Terrain::SIZE))], 1);
			//*tData[int(ceil(edgeTop / Terrain::SIZE))][int(round((edgeLeft + i) / Terrain::SIZE))] = TerraTypes::Air;
		}
		if (* tData[int(ceil(edgeBottom / Terrain::SIZE) + 1)][int(round((edgeRight - i) / Terrain::SIZE))] == TerraTypes::Air) {
			pawn->TouchingSurface(nullptr , 0);
		}
		else {
			pawn->TouchingSurface(tData[int(ceil(edgeBottom / Terrain::SIZE) + 1)][int(round((edgeRight - i) / Terrain::SIZE))], 0);
			//*tData[int(ceil(edgeBottom / Terrain::SIZE) + 1)][int(round((edgeRight - i) / Terrain::SIZE))] = TerraTypes::Air;
		}
		//...
	}
	/// Right and Left Edge Detection
	for (int i = 0; i <= psh; i++) {
		if (_CllArry[edgeTop + i][edgeLeft] != nullptr) {
			pawn->CollisionDetected(_CllArry[edgeTop + i][edgeLeft]);
		}
		else {
			_CllArry[edgeTop + i][edgeLeft] = pawn;
		}
		if (_CllArry[edgeBottom - i][edgeRight] != nullptr) {
			pawn->CollisionDetected(_CllArry[edgeBottom - i][edgeRight]);
		}
		else {
			_CllArry[edgeBottom - i][edgeRight] = pawn;
		}
		//...
		if (* tData[int(round((edgeTop + i)/ Terrain::SIZE))][int(ceil(edgeLeft / Terrain::SIZE))] == TerraTypes::Air) {

		}
		else {

		//	*tData[int(round((edgeTop + i) / Terrain::SIZE))][int(ceil(edgeLeft / Terrain::SIZE))] = TerraTypes::Air;
		}
		if (* tData[int((round(edgeBottom - i)/ Terrain::SIZE))][int(ceil(edgeRight / Terrain::SIZE) + 1)] == TerraTypes::Air) {

		}
		else {

		//	*tData[int((round(edgeBottom - i)/ Terrain::SIZE))][int(ceil(edgeRight / Terrain::SIZE) + 1)] = TerraTypes::Air;
		}
		//...
	}
	///
}

void CollisionField::EmptyCollisionField()
{
	for (int k = 0; k < HEIGHT; k++) {
		for (int i = 0; i < WIDTH; i++) {
			_oldArray[k][i] = _CllArry[k][i];
				_CllArry[k][i] = nullptr;
		}
	}
}

void CollisionField::DrawField( MainWindow & wnd , Graphics & gfx)
{
	for (int k = 0; k < HEIGHT; k++) {
		for (int i = 0; i < WIDTH; i++) {
			if (_oldArray[k][i] == nullptr) {

			}
			else {
				gfx.PutPixel(i, k, 255, 0 , 0);
			}
		}
	}
}
