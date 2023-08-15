#pragma once
#include<wx/wx.h>
#include "LoginInfo.h"
class LoginFrame :public wxFrame
{
public:
	LoginFrame(const wxString& title);
private:
	wxPanel* panel;

	wxStaticText* staticusername;
	wxTextCtrl* usernameLogin;

	wxStaticText* staticPassword;
	wxTextCtrl* passwordLogin;

	wxButton* loginButton;
	wxButton* signupButtonOnloginpage;

	wxButton* backButtonLogin;

	bool LoginSuccess = false;

	void OnBackButtonLoginClick(wxCommandEvent& evt);
	void OnLoginButtonCLick(wxCommandEvent& evt);
	void PasswordChecker();
	void OnSignupButtonCLick(wxCommandEvent& evt);
};

