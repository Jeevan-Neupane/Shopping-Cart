#pragma once
#include <wx/wx.h>
#include"AdminAddedProduct.h"
#include <wx/spinctrl.h>
class AdminPanel : public wxFrame
{
public:
	AdminPanel(const wxString& title, const wxPoint& pos, const wxSize& size);
	void AddOptionToDropdown(const wxString& option);

private:
	wxComboBox* dropdownInput;
	wxTextCtrl* newOptionInput;
	wxButton* addButton;
	wxButton* saveButton;
	wxButton* showProducts;
	wxButton* removeButton;
	wxTextCtrl* resultTextCtrl;

	wxTextCtrl* productNameInput;
	wxTextCtrl* productPriceInput;
	wxSpinCtrl* productRatingInput;
	wxTextCtrl* productDescriptionInput;
	wxSpinCtrl* productQuantityInput; // New input field for quantity
	int lastSerialNumber;

	wxString selectedOption;
	std::vector<AdminAddedProducts> products;
	std::vector<wxButton*> removeButtons;

	void OnAdd(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);

	void OnShowProduct(wxCommandEvent& event);


	void SaveProductToFile(const wxString& category, int serialNo, const AdminAddedProducts& product);

	void SaveOptionsToFile();


	std::vector<wxBoxSizer*> productSizers;
	std::vector<wxButton*> productButtons;

	wxDECLARE_EVENT_TABLE();
};