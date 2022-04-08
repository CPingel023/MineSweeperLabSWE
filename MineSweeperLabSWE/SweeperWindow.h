#pragma once
#include "wx/wx.h"
class SweeperWindow : public wxFrame
{
private:
	int nSweepHeight = 10;
	int nSweepWidth = 10;
	wxButton** sweeps;
	int* nMineField = nullptr;
	bool FirstClicked = true;

public:
	SweeperWindow();
	~SweeperWindow();
	wxDECLARE_EVENT_TABLE();
	void OnButtonClicked(wxCommandEvent& evt);
};

