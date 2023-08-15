#pragma once
#include"wx\wx.h"
#include"LoginInfo.h"
#include<wx/wx.h>
class SignupFrame :public wxFrame
{
public:
	bool messageBoxShown;
	SignupFrame(const wxString& title);
private:
	wxPanel* panel;
	wxStaticText* staticusername;
	wxTextCtrl* username;
	wxStaticText* staticSetPassword;
	wxTextCtrl* setpassword;
	wxStaticText* staticConfirmPassword;
	wxTextCtrl* confirmpassword;
	wxButton* signupButton;
	wxButton* backButtonSignup;

	void PasswordFilter();
	void SaveSignupInfo();
	void OnSignupButtonClick(wxCommandEvent& evt);
	void OnBackButtonSignupClick(wxCommandEvent& evt);
};

