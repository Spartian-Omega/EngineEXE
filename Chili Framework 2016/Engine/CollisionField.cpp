#include "CollisionField.h"
#include "_2D_Vector.h"

CollisionField::CollisionField()
{
	for (int k = 0; k <= 599; k++) {
		for (int i = 0; i <= 799; i++) {
			_pawnArray[k][i] = NULL;
		}
	}
}


CollisionField::~CollisionField()
{
}

void CollisionField::UpdateCollisionField(class Pawn * pawn)
{
	_2D_Point pp = pawn->QueryPosition();
	int ps = pawn->QuerySize();
	int ppx = (int)pp.x;
	int ppy = (int)pp.y;

	int edgeTop = ppy - ps / 2;
	int edgeBottom = ppy + ps / 2;
	int edgeLeft = ppx - ps / 2;
	int edgeRight = ppx + ps / 2;

		for (int i = 0; i < ps; i++) {
			if (_pawnArray[edgeTop][edgeLeft + i + 1] != NULL) {
				pawn->collisionDetected(_pawnArray[edgeTop][edgeLeft + i + 1]);
			}
			else {
				_pawnArray[edgeTop][edgeLeft + i + 1] = pawn;
			}
			if (_pawnArray[edgeBottom][edgeRight - i - 1] != NULL) {
				pawn->collisionDetected(_pawnArray[edgeBottom][edgeRight - i - 1]);
			}
			else {
				_pawnArray[edgeBottom][edgeRight - i - 1] = pawn;
			}
			if (_pawnArray[edgeTop + i][edgeLeft] != NULL) {
				pawn->collisionDetected(_pawnArray[edgeTop + i][edgeLeft]);
			}
			else {
				_pawnArray[edgeTop + i][edgeLeft] = pawn;
			}
			if (_pawnArray[edgeBottom - i][edgeRight] != NULL) {
				pawn->collisionDetected(_pawnArray[edgeBottom - i][edgeRight]);
			}
			else {
				_pawnArray[edgeBottom - i][edgeRight] = pawn;
			}
		
		}

}

void CollisionField::EmptyCollisionField()
{
	for (int k = 0; k <= 599; k++) {
		for (int i = 0; i <= 799; i++) {
				_pawnArray[k][i] = NULL;
		}
	}
}

void CollisionField::DrawField( MainWindow & wnd , Graphics & gfx)
{
	for (int k = 0; k <= 599; k++) {
		for (int i = 0; i <= 799; i++) {
			if (_pawnArray[k][i] == NULL) {

			}
			else {
				gfx.PutPixel(i, k, 255, 0 , 0);
			}
		}
	}
}
