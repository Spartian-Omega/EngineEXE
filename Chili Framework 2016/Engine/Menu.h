#pragma once

#include "Stage.h"



class Menu :
	public Stage
{
public:
	Menu(MainWindow & wnd);
	~Menu();
	
	void StageGo(double dt);
	void UpdateUI(double dt);

protected:

};

