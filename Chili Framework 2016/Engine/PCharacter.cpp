#include "PCharacter.h"


/// Static Variable Declarations

///

PCharacter::PCharacter(_2D_Point p, Shape * s) : PDynamic(p, s)
{
}


PCharacter::~PCharacter()
{
}

void PCharacter::UpdatePawn()
{

}

void PCharacter::MoveHorizontal(int direction, double dt)
{
}

void PCharacter::MoveVertical(int direction, double dt)
{
}

void PCharacter::collisionDetected(Pawn * collidingPawn)
{
}
