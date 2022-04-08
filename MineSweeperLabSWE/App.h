#pragma once
#include "wx/wx.h"

class SweeperWindow;

class App: public wxApp
{
private:
	SweeperWindow* sweeper = nullptr;	
public:
	App();
	~App();
	virtual bool OnInit();
};

