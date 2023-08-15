#include "App.h"
#include "MainLoginFrame.h"
#include<wx/wx.h>

wxIMPLEMENT_APP(App);

 bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("LOGIN PAGE");
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	mainFrame->Show();

	return true;


}