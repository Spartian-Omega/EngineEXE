#pragma once

#include "UserInterface.h"
class MainWindow;


class Stage
{
	friend struct StagePath;
public:
	Stage(MainWindow & wnd);
	virtual ~Stage();

	virtual void StageGo(double dt);
	virtual void UpdateUI(double dt);

	UserInterface GetUI() { return _UI; }

protected:
	bool _nxtStg = false;
	UserInterface _UI;

};


struct StagePath
{
	Stage * CStge = nullptr;
	Stage * NStge = nullptr;

	void StagePathGo() {
		if (CStge->_nxtStg) {
			delete CStge;
			CStge = NStge;
		}
	}
};

