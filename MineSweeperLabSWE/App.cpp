#include "App.h"
#include "SweeperWindow.h"

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {
	sweeper = new SweeperWindow();
	sweeper->Show();
	return true;
}