#pragma once
#include"wx\wx.h"
class AdminFrame :public wxFrame
{
public:
	AdminFrame(const wxString& title);
private:
	void OnAdminButtonClick(wxCommandEvent& evt);
	void OnBackButtonAdminClick(wxCommandEvent& evt);
	wxTextCtrl* usernameAdmin;
	wxTextCtrl* passwordAdmin;
	wxButton* LoginAdminButton;
	wxButton* backButtonAdmin;

};

