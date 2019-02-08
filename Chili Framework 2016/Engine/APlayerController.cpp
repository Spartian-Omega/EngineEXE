#include "APlayerController.h"
#include "PDynamic.h"


APlayerController::APlayerController(PDynamic * pawn, class MainWindow & wnd) : Controller(pawn) , wnd(wnd)
{
	myPawn->SetColour(Color(255, 255, 255));
}


APlayerController::~APlayerController()
{
}

void APlayerController::ControllerGo(double dt)
{
	//_debug_wstream = std::to_wstring(dt);
	//OutputDebugString(L"dt = ");
	//OutputDebugString(_debug_wstream.c_str());
	//OutputDebugString(L"\n");
	//Right Move
	if (wnd.kbd.KeyIsPressed(68)) {
		myPawn->MoveHorizontal(1, dt);
	}
	//Left Move
	else if (wnd.kbd.KeyIsPressed(65)) {
		myPawn->MoveHorizontal(-1, dt);
	}
	//No Move
	else {
		myPawn->MoveHorizontal(0, dt);
	}

	//Down Move
	if (wnd.kbd.KeyIsPressed(83)) {
		myPawn->MoveVertical(1, dt);
	}
	//Up Move
	else if (wnd.kbd.KeyIsPressed(87)) {
		myPawn->MoveVertical(-1, dt);
	}
	//No Move
	else {
		myPawn->MoveVertical(0, dt);
	}
	myPawn->UpdatePawn();

	_ctrlPressed = wnd.kbd.KeyIsPressed(VK_CONTROL);
}

Pawn * APlayerController::GetTarget()
{
	return nullptr;
}
