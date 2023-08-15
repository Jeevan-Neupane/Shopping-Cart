#include "MainLoginFrame.h"
#include<wx/wx.h>
#include"LoginFrame.h"
#include"SignupFrame.h"
#include"AdminFrame.h"


MainFrame::MainFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title) {
	wxPanel* panel = new wxPanel(this);
	wxButton* button1 = new wxButton(panel, wxID_ANY, "Login", wxPoint(300, 100), wxSize(200, -1));
	wxButton* button2 = new wxButton(panel, wxID_ANY, "Signup", wxPoint(300, 140), wxSize(200, -1));
	wxButton* button3 = new wxButton(panel, wxID_ANY, "Login as Administrater", wxPoint(300, 180), wxSize(200, -1));

	button1->Bind(wxEVT_BUTTON, &MainFrame::OnButton1Click, this);
	button2->Bind(wxEVT_BUTTON, &MainFrame::OnButton2Click, this);
	button3->Bind(wxEVT_BUTTON, &MainFrame::OnButton3Click, this);



}
void MainFrame::OnButton1Click(wxCommandEvent& evt) {
	LoginFrame* loginframe = new LoginFrame("Login Page");
	loginframe->SetClientSize(800, 400);
	loginframe->Show(true);
	MainFrame::Close();
}
void MainFrame::OnButton2Click(wxCommandEvent& evt) {
	SignupFrame* signupframe = new SignupFrame("Signup Page");
	signupframe->SetClientSize(800, 400);
	signupframe->Show(true);
	MainFrame::Close();
}
void MainFrame::OnButton3Click(wxCommandEvent& evt) {
	AdminFrame* adminframe = new AdminFrame("Admin Page");
	adminframe->SetClientSize(800, 400);
	adminframe->Show(true);
	MainFrame::Close();
}

