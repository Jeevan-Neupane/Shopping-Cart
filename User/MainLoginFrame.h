#include<wx/wx.h>
class LoginFrame;
class MainFrame :public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void OnButton1Click(wxCommandEvent& evt);
	void OnButton2Click(wxCommandEvent& evt);
	void OnButton3Click(wxCommandEvent& evt);
};

