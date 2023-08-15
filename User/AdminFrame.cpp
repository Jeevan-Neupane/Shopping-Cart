#include "AdminFrame.h"
#include "MainLoginFrame.h"
#include "AdminPanel.h"
#include <fstream>
AdminFrame::AdminFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title) {
	wxPanel* panel = new wxPanel(this);

	wxStaticText* staticusername = new wxStaticText(panel, wxID_ANY, "Admin access", wxPoint(300, 80), wxSize(100, -1));
	usernameAdmin = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(300, 100), wxSize(200, -1));

	wxStaticText* staticSetPassword = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(300, 120), wxSize(100, -1));
	passwordAdmin = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(300, 140), wxSize(200, -1), wxTE_PASSWORD);

	backButtonAdmin = new wxButton(panel, wxID_ANY, "back", wxPoint(700, 350), wxSize(50, -1));

	LoginAdminButton = new wxButton(panel, wxID_ANY, "Login", wxPoint(300, 210), wxSize(100, -1));

	LoginAdminButton->Bind(wxEVT_BUTTON, &AdminFrame::OnAdminButtonClick, this);


	backButtonAdmin->Bind(wxEVT_BUTTON, &AdminFrame::OnBackButtonAdminClick, this);


}

void AdminFrame::OnAdminButtonClick(wxCommandEvent& evt)
{

	wxString userAdminInfo = AdminFrame::usernameAdmin->GetValue();
	wxString passwordAdminInfo = AdminFrame::passwordAdmin->GetValue();

	if (userAdminInfo == "admin" && passwordAdminInfo == "admin") {
		AdminPanel* frame = new AdminPanel("Dynamic Dropdown Input", wxPoint(50, 50), wxSize(1000, 800));
		wxFont font(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);



		std::ifstream optionsFile("options.txt");
		if (optionsFile.is_open())
		{
			std::string option;
			while (std::getline(optionsFile, option))
			{
				wxString wxOption(option);
				frame->AddOptionToDropdown(wxOption);
			}
			optionsFile.close();
		}

		frame->Show(true);
		
		/*AdminFrame::Close();*/
	}


}

void AdminFrame::OnBackButtonAdminClick(wxCommandEvent& evt)
{
	MainFrame* mainFrame = new MainFrame("LOGIN PAGE");
	mainFrame->SetClientSize(800, 400);
	mainFrame->Show(true);
	AdminFrame::Close();
}
