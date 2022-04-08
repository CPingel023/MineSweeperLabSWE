#include "SweeperWindow.h"


wxBEGIN_EVENT_TABLE(SweeperWindow, wxFrame)
EVT_BUTTON(1001, OnButtonClicked)
wxEND_EVENT_TABLE()

SweeperWindow::SweeperWindow() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(200, 200), wxSize(800, 800)) {
	sweeps = new wxButton * [nSweepWidth * nSweepHeight];
	wxGridSizer* grid = new wxGridSizer(nSweepWidth, nSweepHeight, 0, 0);

	nMineField = new int[nSweepWidth * nSweepHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < nSweepWidth; x++) {
		for (int y = 0; y < nSweepHeight; y++) {
			sweeps[y * nSweepWidth + x] = new wxButton(this, 10000 + (y * nSweepWidth + x));
			sweeps[y * nSweepWidth + x]->SetFont(font);
			grid->Add(sweeps[y * nSweepWidth + x], 1, wxEXPAND | wxALL);

			sweeps[y * nSweepWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &SweeperWindow::OnButtonClicked, this);
			nMineField[y * nSweepWidth + x] = 0;
		}
	}
	this->SetSizer(grid);
	grid->Layout();
}

SweeperWindow::~SweeperWindow() {
	delete[] sweeps;
}

void SweeperWindow::OnButtonClicked(wxCommandEvent& evt) {
	int x = (evt.GetId() - 10000) % nSweepWidth;
	int y = (evt.GetId() - 10000) / nSweepWidth;
	if (FirstClicked) {
		int mines = 30;
		while (mines) {
			int rx = rand() % nSweepWidth;
			int ry = rand() % nSweepHeight;

			if (nMineField[ry * nSweepWidth + rx] == 0 && rx != x && ry != y){
				nMineField[ry * nSweepWidth + rx] = -1;
				mines--;
			}
		}
		FirstClicked = false;
	}

	sweeps[y * nSweepWidth + x]->Enable(false);
	if (nMineField[y * nSweepWidth + x] == -1) {
		wxMessageBox("Well, nice try. Guess you lost :( Good luck next time!");
		FirstClicked = true;

		for (int x = 0; x < nSweepWidth; x++) {
			for (int y = 0; y < nSweepHeight; y++) {
				nMineField[y * nSweepWidth + x] = 0;
				
				sweeps[y * nSweepWidth + x]->SetLabel("");
				sweeps[y * nSweepWidth + x]->Enable(true);
			}
		}
	}
	else {
		int neighborMines = 0;
		for (int i = -1; i < 2; i++) 
		{
			for (int j = -1; j < 2; j++) 
			{
				if (x + i >= 0 && x + i < nSweepWidth && y + j >= 0 && y + j < nSweepHeight) 
				{
					if (nMineField[(y + j) * nSweepWidth + (x + i)] == -1) 
					{
						neighborMines++;
					}
				}
			}
		}
		if (neighborMines > 0) {
			sweeps[y * nSweepWidth + x]->SetLabel(std::to_string(neighborMines));
		}
	}



	evt.Skip();
}