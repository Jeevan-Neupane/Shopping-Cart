#include "UserFrame.h"
#include <sstream>
#include <fstream>
#include "Cart.h"


UserFrame::UserFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size) {

	std::ifstream inputFile("all_products.txt");
	if (inputFile.is_open()) {
		std::string line;
		while (std::getline(inputFile, line)) {
			std::istringstream iss(line);
			std::string isSelected_str, name, price_str, quantity_str;
			if (std::getline(iss, isSelected_str, '_') &&
				std::getline(iss, name, '_') &&
				std::getline(iss, price_str, '_') &&
				std::getline(iss, quantity_str, '_')) {

				int isSelected = std::stoi(isSelected_str);
				int price = std::stoi(price_str);
				int quantity = std::stoi(quantity_str);

				Product product(isSelected, name, price, quantity);
				allProducts.push_back(product);
			}
		}
		inputFile.close();
	}
	wxFont font(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	mainSizer = new wxBoxSizer(wxVERTICAL);
	searchField = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	searchButton = new wxButton(this, wxID_ANY, "Search");
	searchButton->SetFont(font);
	searchField->SetFont(font);
	// Bind events for the search field and button
	searchField->Bind(wxEVT_TEXT_ENTER, &UserFrame::OnSearch, this);
	searchButton->Bind(wxEVT_BUTTON, &UserFrame::OnSearch, this);

	// Create a horizontal sizer for the search components
	wxBoxSizer* searchSizer = new wxBoxSizer(wxHORIZONTAL);
	searchSizer->Add(searchField, 1, wxEXPAND | wxALL, 5);
	searchSizer->Add(searchButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	// Add the search sizer to the main sizer
	mainSizer->Insert(0, searchSizer, 0, wxEXPAND | wxALL, 5);
	displayButton = new wxButton(this, wxID_ANY, "Cart");
	displayButton->SetFont(font);
	displayButton->Bind(wxEVT_BUTTON, &UserFrame::OnDisplaySelected, this);

	mainSizer->Insert(0, displayButton, 0, wxALL | wxALIGN_CENTER, 5);

	for (size_t i = 0; i < allProducts.size(); ++i) {
		wxCheckBox* checkBox = new wxCheckBox(this, wxID_ANY,
			wxString::Format("%s - Price: %d - Quantity: %d", allProducts[i].GetName(), allProducts[i].GetPrice(), allProducts[i].GetQuantity()));
		checkBox->Bind(wxEVT_CHECKBOX, &UserFrame::OnCheckBox, this);
		checkBox->SetValue(allProducts[i].GetIsSelected() != 0);
		checkBox->SetFont(font);
		mainSizer->Add(checkBox, 0, wxALL, 5);
		checkBoxes.push_back(checkBox);

		wxSpinCtrl* spinCtrl = new wxSpinCtrl(this, wxID_ANY, wxString::Format("%d", allProducts[i].GetQuantity()));
		spinCtrl->Bind(wxEVT_SPINCTRL, &UserFrame::OnSpinCtrl, this);
		spinCtrl->SetValue(allProducts[i].GetQuantity());
		mainSizer->Add(spinCtrl, 0, wxALL, 5);
		mainSizer->AddSpacer(20);
		spinCtrls.push_back(spinCtrl);
	}


	this->SetSizerAndFit(mainSizer);
}


void UserFrame::OnSearch(wxCommandEvent& event) {
	wxString searchText = searchField->GetValue().Lower(); // Convert search text to lowercase

	// Filter products based on the search text
	filteredProducts.clear();
	for (const Product& product : allProducts) {
		wxString productName = wxString::FromUTF8(product.GetName().c_str()).Lower(); // Convert product name to lowercase
		if (productName.find(searchText) != wxString::npos) {
			filteredProducts.push_back(product);
		}
	}

	// Clear existing checkboxes and spin controls
	for (wxCheckBox* checkBox : checkBoxes) {
		checkBox->Destroy();
	}
	checkBoxes.clear();

	for (wxSpinCtrl* spinCtrl : spinCtrls) {
		spinCtrl->Destroy();
	}
	spinCtrls.clear();

	// Check if no products were found
	if (filteredProducts.empty()) {
		wxStaticText* notFoundLabel = new wxStaticText(this, wxID_ANY, "No products found.");
		mainSizer->Add(notFoundLabel, 0, wxALL, 5);
	}
	else {
		// Populate checkboxes and spin controls with filtered products
		for (size_t i = 0; i < filteredProducts.size(); ++i) {
			wxCheckBox* checkBox = new wxCheckBox(this, wxID_ANY,
				wxString::Format("%s - Price: %d - Quantity: %d", filteredProducts[i].GetName(), filteredProducts[i].GetPrice(), filteredProducts[i].GetQuantity()));
			checkBox->Bind(wxEVT_CHECKBOX, &UserFrame::OnCheckBox, this);
			checkBox->SetValue(filteredProducts[i].GetIsSelected() != 0);
			mainSizer->Add(checkBox, 0, wxALL, 5);
			checkBoxes.push_back(checkBox);

			wxSpinCtrl* spinCtrl = new wxSpinCtrl(this, wxID_ANY, wxString::Format("%d", filteredProducts[i].GetQuantity()));
			spinCtrl->Bind(wxEVT_SPINCTRL, &UserFrame::OnSpinCtrl, this);
			spinCtrl->SetValue(filteredProducts[i].GetQuantity());
			mainSizer->Add(spinCtrl, 0, wxALL, 5);
			spinCtrls.push_back(spinCtrl);
		}
	}

	// Update the layout
	this->Layout();
}

void UserFrame::OnDisplaySelected(wxCommandEvent& event) {
	std::vector<Product> selectedProducts;
	for (size_t i = 0; i < allProducts.size(); ++i) {
		if (allProducts[i].GetIsSelected() != 0) {
			selectedProducts.push_back(allProducts[i]);
		}
	}

	if (!selectedProducts.empty()) {
		SelectedItemsFrame* selectedItemsFrame = new SelectedItemsFrame(selectedProducts);
		selectedItemsFrame->Show();
	}
}



void UserFrame::OnCheckBox(wxCommandEvent& event) {
	wxCheckBox* checkBox = static_cast<wxCheckBox*>(event.GetEventObject());
	int index = std::find(checkBoxes.begin(), checkBoxes.end(), checkBox) - checkBoxes.begin();

	if (index >= 0 && index < static_cast<int>(filteredProducts.size())) {
		bool isChecked = checkBox->GetValue();
		filteredProducts[index].SetIsSelected(isChecked ? 1 : 0);

		// Update the selection status in the allProducts vector as well
		for (Product& product : allProducts) {
			if (product.GetName() == filteredProducts[index].GetName()) {
				product.SetIsSelected(isChecked ? 1 : 0);
				break;
			}
		}

		UpdateFile();
	}
}



void UserFrame::OnSpinCtrl(wxSpinEvent& event) {
	wxSpinCtrl* spinCtrl = static_cast<wxSpinCtrl*>(event.GetEventObject());
	int index = std::find(spinCtrls.begin(), spinCtrls.end(), spinCtrl) - spinCtrls.begin();

	if (index >= 0 && index < static_cast<int>(filteredProducts.size())) {
		int newQuantity = spinCtrl->GetValue();
		filteredProducts[index].SetQuantity(newQuantity);

		// Update the quantity in the allProducts vector as well
		for (Product& product : allProducts) {
			if (product.GetName() == filteredProducts[index].GetName()) {
				product.SetQuantity(newQuantity);
				break;
			}
		}

		wxString newText = wxString::Format("%s - Price: %d - Quantity: %d", filteredProducts[index].GetName(), filteredProducts[index].GetPrice(), newQuantity);
		checkBoxes[index]->SetLabel(newText);

		UpdateFile();
	}
}

void UserFrame::UpdateFile() {
	std::ofstream outputFile("all_products.txt");
	if (outputFile.is_open()) {
		for (const Product& product : allProducts) {
			outputFile << product.GetIsSelected() << "_"
				<< product.GetName() << "_"
				<< product.GetPrice() << "_"
				<< product.GetQuantity() << "\n";
		}
		outputFile.close();
	}
}
