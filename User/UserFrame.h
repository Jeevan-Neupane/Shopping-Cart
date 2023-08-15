#pragma once
#include <wx/wx.h>
#include "Product.h"
#include <wx/spinctrl.h>

class UserFrame : public wxFrame {
public:
	UserFrame(const wxString& title, const wxPoint& pos, const wxSize& size);



private:
	std::vector<wxCheckBox*> checkBoxes;
	std::vector<wxSpinCtrl*> spinCtrls;
	wxButton* displayButton;

	void OnCheckBox(wxCommandEvent& event);
	void OnSpinCtrl(wxSpinEvent& event);
	void OnDisplaySelected(wxCommandEvent& event);
	void OnSearch(wxCommandEvent& event);

	void UpdateFile();
	wxTextCtrl* searchField;
	wxButton* searchButton;
	wxBoxSizer* mainSizer;
	std::vector<Product> allProducts;

	std::vector<Product> filteredProducts;


};