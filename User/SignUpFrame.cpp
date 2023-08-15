#include "SignupFrame.h"
#include "LoginInfo.h"
#include "LoginFrame.h"
#include<wx/wx.h>
#include "MainLoginFrame.h"
SignupFrame::SignupFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	messageBoxShown = false;
	panel = new wxPanel(this);

	staticusername = new wxStaticText(panel, wxID_ANY, "Username", wxPoint(300, 80), wxSize(100, -1));
	username = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(300, 100), wxSize(200, -1));

	staticSetPassword = new wxStaticText(panel, wxID_ANY, "Set Password", wxPoint(300, 120), wxSize(100, -1));
	setpassword = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(300, 140), wxSize(200, -1), wxTE_PASSWORD);

	staticConfirmPassword = new wxStaticText(panel, wxID_ANY, "Confirm Password", wxPoint(300, 160), wxSize(100, -1));
	confirmpassword = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(300, 180), wxSize(200, -1), wxTE_PASSWORD);

	signupButton = new wxButton(panel, wxID_ANY, "Signup", wxPoint(300, 210), wxSize(100, -1));

	backButtonSignup = new wxButton(panel, wxID_ANY, "back", wxPoint(700, 350), wxSize(50, -1));

	signupButton->Bind(wxEVT_BUTTON, &SignupFrame::OnSignupButtonClick, this);
	backButtonSignup->Bind(wxEVT_BUTTON, &SignupFrame::OnBackButtonSignupClick, this);

}

void SignupFrame::OnSignupButtonClick(wxCommandEvent& evt) {
	//filters password
	messageBoxShown = false;
	PasswordFilter();

	if (messageBoxShown == true) {
		return;
	}
	//loads info to file
	SaveSignupInfo();
	//opening login window
	LoginFrame* loginframe = new LoginFrame("Login Page");
	loginframe->SetClientSize(800, 400);
	loginframe->Show(true);
	SignupFrame::Close();
}

void SignupFrame::OnBackButtonSignupClick(wxCommandEvent& evt2)
{
	MainFrame* mainFrame = new MainFrame("LOGIN PAGE");
	mainFrame->SetClientSize(800, 400);
	mainFrame->Show(true);
	SignupFrame::Close();
}

void SignupFrame::PasswordFilter() {
	wxString setPassValue = SignupFrame::setpassword->GetValue();
	wxString confirmPassValue = SignupFrame::confirmpassword->GetValue();
	if (setPassValue != confirmPassValue) {
		wxMessageBox("Please confirm your password again as set and confirmed password are not same!!!");
		messageBoxShown = true;
		return;
	}
	if (confirmPassValue.size() < 8) {
		wxMessageBox("Your password should be at least 8 letter long!!!");
		messageBoxShown = true;
		return;
	}


	bool alphabet = false;
	bool numbers = false;
	bool symbols = false;

	for (int i = 0; i < confirmPassValue.size(); i++) {
		//checking for alphabet in our password
		int ascii = int(confirmPassValue[i]);
		if ((ascii <= 90 && ascii >= 65)
			|| (ascii <= 122 && ascii >= 97)) {
			alphabet = true;
		}
		//checking for numbers in our password
		if (ascii <= 57 && ascii >= 48) {
			numbers = true;
		}
		//checking for symbols in our password
		if ((ascii <= 47 && ascii >= 33)
			|| (ascii <= 64 && ascii >= 58)
			|| (ascii <= 96 && ascii >= 91)
			|| (ascii <= 123 && ascii >= 126)) {

			symbols = true;
		}
	}

	if (alphabet == false) {
		wxMessageBox("Your password should have at least one alphabet!!!");
		messageBoxShown = true;
		return;
	}

	if (numbers == false) {
		wxMessageBox("Your password should have at least one number!!!");
		messageBoxShown = true;
		return;
	}

	if (symbols == false) {
		wxMessageBox("Your password should have at least one symbol");
		messageBoxShown = true;
		return;
	}




}

void SignupFrame::SaveSignupInfo() {
	std::vector<LoginInfo> Informationvector;
	LoginInfo UserInfo;
	UserInfo.UsernameInformation = SignupFrame::username->GetValue();
	UserInfo.PasswordInformation = SignupFrame::confirmpassword->GetValue();
	Informationvector.push_back(UserInfo);

	saveUserInfoToFile(Informationvector, "UserLoginInformation.txt");

}


