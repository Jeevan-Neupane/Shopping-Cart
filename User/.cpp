#include "MyApp.h"
#include "MyFrame.h"

bool MyApp::OnInit() {
	MyFrame* frame = new MyFrame("Product List", wxPoint(50, 50), wxSize(600, 400));
	frame->Show(true);
	frame->SetSize(1000, 800);



	return true;
}

wxIMPLEMENT_APP(MyApp);