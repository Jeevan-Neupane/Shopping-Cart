#include "LoginFrame.h"
#include "MainLoginFrame.h"
#include "LoginInfo.h"
#include "SignupFrame.h"
#include "UserFrame.h"
LoginFrame::LoginFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title) {
	panel = new wxPanel(this);

	staticusername = new wxStaticText(panel, wxID_ANY, "Username", wxPoint(300, 80), wxSize(100, -1));
	usernameLogin = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(300, 100), wxSize(200, -1));

	staticPassword = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(300, 120), wxSize(100, -1));
	passwordLogin = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(300, 140), wxSize(200, -1), wxTE_PASSWORD);

	loginButton = new wxButton(panel, wxID_ANY, "Login", wxPoint(300, 210), wxSize(100, -1));

	signupButtonOnloginpage = new wxButton(panel, wxID_ANY, "Signup First", wxPoint(400, 210), wxSize(100, -1));

	backButtonLogin = new wxButton(panel, wxID_ANY, "back", wxPoint(700, 350), wxSize(50, -1));

	loginButton->Bind(wxEVT_BUTTON, &LoginFrame::OnLoginButtonCLick, this);

	signupButtonOnloginpage->Bind(wxEVT_BUTTON, &LoginFrame::OnSignupButtonCLick, this);

	backButtonLogin->Bind(wxEVT_BUTTON, &LoginFrame::OnBackButtonLoginClick, this);
}

void LoginFrame::OnBackButtonLoginClick(wxCommandEvent& evt)
{
	MainFrame* mainFrame = new MainFrame("LOGIN PAGE");
	mainFrame->SetClientSize(800, 400);
	mainFrame->Show(true);
	LoginFrame::Close();
}

void LoginFrame::OnLoginButtonCLick(wxCommandEvent& evt)
{
	//LoadLoginInfo();
	PasswordChecker();

	if (LoginSuccess == true) {
		UserFrame* userframe = new UserFrame("Product List", wxPoint(50, 50), wxSize(600, 400));
		userframe->SetClientSize(800, 400);
		userframe->Show(true);
		//LoginFrame::Close();
		
		wxMessageBox("login successfull!!!");
		return;


	}
	if (LoginSuccess == false) {
		wxMessageBox("Password or username INCORRECT!!!");
		return;
	}
	/*SignupFrame* signupframe = new SignupFrame("Signup Page");
	signupframe->SetClientSize(800, 400);
	signupframe->Show(true);
	LoginFrame::Close();
*/



}


//void LoadLoginInfo() {

	//std::vector<LoginInfo>informationvector = loadUserInfoFromFile("UserLoginInformation.txt");



//}

void LoginFrame::PasswordChecker() {
	wxString LoginUsernameInformation = LoginFrame::usernameLogin->GetValue();
	wxString LoginPasswordInformation = LoginFrame::passwordLogin->GetValue();


	std::vector<LoginInfo>informationvector = loadUserInfoFromFile("UserLoginInformation.txt");

	if (informationvector.empty()) {
		LoginSuccess = false;
		return;

	}
	LoginSuccess = false;


	for (const LoginInfo& Info : informationvector) {
		if ((Info.UsernameInformation == LoginUsernameInformation)
			&& (Info.PasswordInformation == LoginPasswordInformation)) {
			LoginSuccess = true;
			break;
		}

	}



}

void LoginFrame::OnSignupButtonCLick(wxCommandEvent& evt)
{
	SignupFrame* signupframe = new SignupFrame("Signup Page");
	signupframe->SetClientSize(800, 400);
	signupframe->Show(true);
	LoginFrame::Close();
}
