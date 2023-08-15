#include "AdminPanel.h"
#include "AdminAddedProduct.h"

#include <wx/wx.h>
#include <fstream>
#include <vector>
#include <wx/filename.h>
#include <wx/spinctrl.h>
#include <wx/dir.h>
#include <wx/tokenzr.h>

enum
{
	ID_AddButton = wxID_HIGHEST + 1,
	ID_SaveButton,
	ID_SubmitButton,
	ID_NewFrameButton,
	ID_DeleteButton
};


wxBEGIN_EVENT_TABLE(AdminPanel, wxFrame)
EVT_BUTTON(ID_AddButton, AdminPanel::OnAdd)
EVT_BUTTON(ID_SaveButton, AdminPanel::OnSave)

EVT_BUTTON(ID_NewFrameButton, AdminPanel::OnShowProduct)


wxEND_EVENT_TABLE()



void AdminPanel::AddOptionToDropdown(const wxString& option)
{
	dropdownInput->Append(option);
}


AdminPanel::AdminPanel(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size), lastSerialNumber(0)
{
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxFont font(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	dropdownInput = new wxComboBox(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN);
	dropdownInput->SetFont(font);
	newOptionInput = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	newOptionInput->SetFont(font);

	addButton = new wxButton(panel, ID_AddButton, "Add Category");
	addButton->SetFont(font);
	saveButton = new wxButton(panel, ID_SaveButton, "Save Product");
	saveButton->SetFont(font);
	showProducts = new wxButton(panel, ID_NewFrameButton, "Show Products");
	showProducts->SetFont(font);
	resultTextCtrl = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

	productNameInput = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	productNameInput->SetFont(font);
	productPriceInput = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	productPriceInput->SetFont(font);
	productRatingInput = new wxSpinCtrl(panel, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 5, 0);
	productRatingInput->SetFont(font);
	productDescriptionInput = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	productDescriptionInput->SetFont(font);
	productQuantityInput = new wxSpinCtrl(panel, wxID_ANY, "1", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100, 1); // Quantity input field
	productQuantityInput->SetFont(font);

	productNameInput->SetHint("Product Name");
	productPriceInput->SetHint("Product Price");
	productDescriptionInput->SetHint("Product Description");

	mainSizer->Add(dropdownInput, 0, wxALL | wxEXPAND, 10);
	mainSizer->Add(newOptionInput, 0, wxALL | wxEXPAND, 10);
	mainSizer->Add(addButton, 0, wxALL | wxEXPAND, 10);
	mainSizer->Add(productNameInput, 0, wxALL | wxEXPAND, 10);
	mainSizer->Add(productPriceInput, 0, wxALL | wxEXPAND, 10);
	mainSizer->Add(productRatingInput, 0, wxALL | wxEXPAND, 10);
	mainSizer->Add(productDescriptionInput, 1, wxALL | wxEXPAND, 10);
	mainSizer->Add(productQuantityInput, 0, wxALL | wxEXPAND, 10); // Add quantity input to the main sizer
	mainSizer->Add(saveButton, 0, wxALL | wxEXPAND, 10);
	mainSizer->Add(resultTextCtrl, 0, wxALL | wxEXPAND, 10);
	mainSizer->Add(showProducts, 0, wxALL | wxEXPAND, 10);


	panel->SetSizerAndFit(mainSizer);
	Centre();

	addButton->Bind(wxEVT_BUTTON, &AdminPanel::OnAdd, this);
	saveButton->Bind(wxEVT_BUTTON, &AdminPanel::OnSave, this);
	showProducts->Bind(wxEVT_BUTTON, &AdminPanel::OnShowProduct, this);

	std::ifstream lastSerialFile("last_serial.txt");
	if (lastSerialFile.is_open()) {
		lastSerialFile >> lastSerialNumber;
		lastSerialFile.close();
	}
	lastSerialNumber++;


}


void AdminPanel::OnShowProduct(wxCommandEvent& event) {
	wxString selectedCategory = dropdownInput->GetValue();
	if (selectedCategory.IsEmpty()) {
		wxMessageBox("Please select a category.", "No Category Selected", wxOK | wxICON_WARNING);
		return; // Exit the function if no category is selected
	}

	wxFrame* productFrame = new wxFrame(NULL, wxID_ANY, "Products of " + selectedCategory, wxDefaultPosition, wxSize(800, 600));
	wxFont font(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	// Create a scrolled window inside the product frame
	wxScrolledWindow* scrolledWindow = new wxScrolledWindow(productFrame, wxID_ANY);

	scrolledWindow->SetScrollRate(10, 10); // Adjust scroll rate as needed

	wxBoxSizer* productSizer = new wxBoxSizer(wxVERTICAL);

	// Construct the file name for the selected category's products
	wxString dirName = "Admin"; // Directory name
	wxString fileName = dirName + wxFileName::GetPathSeparator() + selectedCategory + "_products.txt";

	// Open the file and read the products
	std::ifstream productFile(fileName.ToStdString());
	if (productFile.is_open()) {
		std::string line;

		while (std::getline(productFile, line)) {
			wxStringTokenizer tokenizer(wxString(line), "_");
			wxString serialNo = tokenizer.GetNextToken();
			wxString name = tokenizer.GetNextToken();
			wxString price = tokenizer.GetNextToken();
			wxString rating = tokenizer.GetNextToken();
			wxString quantity = tokenizer.GetNextToken();
			wxString description = tokenizer.GetNextToken();

			// Create a box to hold product information and delete button
			wxBoxSizer* productBoxSizer = new wxBoxSizer(wxHORIZONTAL);

			// Create a checkbox for the product


			// Create a product information string
			wxString productInfo = "Serial No: " + serialNo + "\n"
				+ "Name: " + name + "\n"
				+ "Price: " + price + "\n"
				+ "Rating: " + rating + "\n"
				+ "Quantity: " + quantity + "\n"
				+ "Description: " + description + "\n\n";

			// Create a static text widget to display the product information
			wxStaticText* productText = new wxStaticText(scrolledWindow, wxID_ANY, productInfo);
			productText->SetFont(font);
			productBoxSizer->Add(productText, 1, wxALL | wxEXPAND, 10);






			productSizer->Add(productBoxSizer, 0, wxEXPAND);

		}

		productFile.close();
	}

	scrolledWindow->SetSizer(productSizer); // Set the productSizer as the sizer for the scrolled window

	// Show the product frame
	productFrame->Show(true);
}


void AdminPanel::OnSave(wxCommandEvent& event)
{
	wxString categoryName = dropdownInput->GetValue();
	wxString productName = productNameInput->GetValue();
	wxString productPriceStr = productPriceInput->GetValue();
	wxString productDescription = productDescriptionInput->GetValue();
	double productPrice = 0.0;
	productPriceStr.ToDouble(&productPrice);
	std::ofstream lastSerialFile("last_serial.txt");
	if (lastSerialFile.is_open()) {
		lastSerialFile << lastSerialNumber;
		lastSerialFile.close();
	}

	int productRating = productRatingInput->GetValue();
	int productQuantity = productQuantityInput->GetValue();

	if (!categoryName.IsEmpty())
	{
		if (!productName.IsEmpty() && productPrice > 0 && !productDescription.IsEmpty())
		{
			AdminAddedProducts newProduct(productName, productPrice, productRating, productDescription, productQuantity);
			productNameInput->Clear();
			productPriceInput->Clear();
			productDescriptionInput->Clear();
			productRatingInput->SetValue(0);
			productQuantityInput->SetValue(1);

			// Increment the serial number
			lastSerialNumber++;

			// Save the product with the incremented serial number
			SaveProductToFile(categoryName, lastSerialNumber, newProduct);

			products.push_back(newProduct);
		}
	}
	else
	{
		wxMessageBox("Please select a category.", "Category Missing", wxOK | wxICON_WARNING);
	}
}



void AdminPanel::OnAdd(wxCommandEvent& event)
{
	wxString newCategory = newOptionInput->GetValue();
	if (!newCategory.IsEmpty())
	{
		dropdownInput->Append(newCategory);
		newOptionInput->Clear();
		SaveOptionsToFile(); // Save the new option to the options file
	}
}


void AdminPanel::SaveProductToFile(const wxString& category, int serialNo, const AdminAddedProducts& product)
{
	wxString dirName = "Admin";
	wxString userDirName = "User";
	wxFileName dirPath(wxGetCwd(), dirName);
	wxFileName userDirPath(wxGetCwd(), userDirName);


	if (!wxDirExists(dirPath.GetFullPath()))
	{
		wxMkdir(dirPath.GetFullPath(), wxS_DIR_DEFAULT);
	}
	if (!wxDirExists(userDirPath.GetFullPath()))
	{
		wxMkdir(userDirPath.GetFullPath(), wxS_DIR_DEFAULT);
	}
	wxString fileName = dirPath.GetFullPath() + wxFileName::GetPathSeparator() + category + "_products.txt";
	wxString userFileName = userDirPath.GetFullPath() + wxFileName::GetPathSeparator() + category + "_products.txt";
	wxString allProducts = "C:/Users/jeevan/OneDrive/Desktop/Final/User/User/all_products.txt";
	std::ofstream file(fileName.ToStdString(), std::ios::app);
	if (file)
	{
		file << serialNo << "_"; // Serial number
		file << product.GetName() << "_"; // Product name
		file << product.GetPrice() << "_"; // Product price
		file << product.GetRating() << "_"; // Product rating
		file << product.GetQuantity() << "_"; // Product quantity
		file << product.GetDescription() << "\n"; // Product description
		file.close();
	}
	std::ofstream userFile(userFileName.ToStdString(), std::ios::app);
	if (userFile)
	{

		userFile << 0 << "_";
		userFile << product.GetName() << "_"; // Product name
		userFile << product.GetPrice() << "_"; // Product price
		userFile << product.GetRating() << "_"; // Product rating
		userFile << product.GetQuantity() << "\n"; // Product quantity

		userFile.close();
	}
	std::ofstream allProductsFile(allProducts.ToStdString(), std::ios::app);
	if (allProductsFile)
	{

		allProductsFile << 0 << "_";
		allProductsFile << product.GetName() << "_"; // Product name
		allProductsFile << product.GetPrice() << "_"; // Product price

		allProductsFile << product.GetQuantity() << "\n"; // Product quantity

		allProductsFile.close();
	}
}

void AdminPanel::SaveOptionsToFile()
{
	std::ofstream optionsFile("options.txt");
	if (optionsFile)
	{
		for (size_t i = 0; i < dropdownInput->GetCount(); ++i)
		{
			wxString option = dropdownInput->GetString(i);
			optionsFile << option << "\n";
		}
		optionsFile.close();
	}
}