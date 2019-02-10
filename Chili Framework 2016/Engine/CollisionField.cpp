#include "CollisionField.h"
#include "_2D_Vector.h"

CollisionField::CollisionField(const int & w, const int & h) : WIDTH(w) , HEIGHT(h)
{
	_CllArry = new Pawn**[HEIGHT];
	_oldArray = new Pawn**[HEIGHT];
	for (int i = 0; i < HEIGHT; i++) {
		_CllArry[i] = new Pawn*[WIDTH];
		_oldArray[i] = new Pawn*[WIDTH];
	}
}


CollisionField::~CollisionField()
{
}

void CollisionField::UpdateCollisionField(class Pawn * pawn)
{
	_2D_Point pp = pawn->QueryPosition();
	int psh = pawn->QuerySizeH();
	int psw = pawn->QuerySizeW();
	int ppx = (int)pp.x;
	int ppy = (int)pp.y;

	int edgeTop = ppy - psh / 2;
	int edgeBottom = ppy + psh / 2;
	int edgeLeft = ppx - psw / 2;
	int edgeRight = ppx + psw / 2;

		for (int i = 0; i < psw; i++) {
			if (_CllArry[edgeTop][edgeLeft + i + 1] != nullptr) {
				pawn->collisionDetected(_CllArry[edgeTop][edgeLeft + i + 1]);
			}
			else {
				_CllArry[edgeTop][edgeLeft + i + 1] = pawn;
			}
			if (_CllArry[edgeBottom][edgeRight - i - 1] != nullptr) {
				pawn->collisionDetected(_CllArry[edgeBottom][edgeRight - i - 1]);
			}
			else {
				_CllArry[edgeBottom][edgeRight - i - 1] = pawn;
			}		
		}
		for (int i = 0; i < psh; i++) {
			if (_CllArry[edgeTop + i][edgeLeft] != nullptr) {
				pawn->collisionDetected(_CllArry[edgeTop + i][edgeLeft]);
			}
			else {
				_CllArry[edgeTop + i][edgeLeft] = pawn;
			}
			if (_CllArry[edgeBottom - i][edgeRight] != nullptr) {
				pawn->collisionDetected(_CllArry[edgeBottom - i][edgeRight]);
			}
			else {
				_CllArry[edgeBottom - i][edgeRight] = pawn;
			}
		}
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
