#include "Cart.h"


SelectedItemsFrame::SelectedItemsFrame(const std::vector<Product>& selectedProducts)
	: wxFrame(NULL, wxID_ANY, "Selected Items", wxDefaultPosition, wxSize(600, 400)) {

	grid = new wxGrid(this, wxID_ANY);
	grid->CreateGrid(selectedProducts.size() + 1, 4); // Add 1 for the total row

	grid->SetColLabelValue(0, "Item Name");
	grid->SetColLabelValue(1, "Quantity");
	grid->SetColLabelValue(2, "Price");
	grid->SetColLabelValue(3, "Total");

	// Populate the grid with data from selectedProducts
	UpdateGrid(selectedProducts);

	// Add the total row
	int total = 0;
	for (size_t i = 0; i < selectedProducts.size(); ++i) {
		total += selectedProducts[i].GetQuantity() * selectedProducts[i].GetPrice();
	}
	grid->SetCellValue(selectedProducts.size(), 0, "Total");
	grid->SetCellValue(selectedProducts.size(), 3, wxString::Format("%d", total));

	// Set cells in the total row as read-only
	for (int col = 0; col < grid->GetNumberCols(); ++col) {
		grid->SetReadOnly(selectedProducts.size(), col, true);
	}

	// Create and add an "Order" button
	wxButton* orderButton = new wxButton(this, wxID_ANY, "Place Order");


	// Add the grid and button to the sizer
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(grid, 1, wxALL | wxEXPAND, 5);
	mainSizer->Add(orderButton, 0, wxALIGN_RIGHT | wxALL, 10);

	this->SetSizerAndFit(mainSizer);
}

void SelectedItemsFrame::UpdateGrid(const std::vector<Product>& selectedProducts) {
	for (size_t i = 0; i < selectedProducts.size(); ++i) {

		grid->SetCellValue(i, 0, selectedProducts[i].GetName());
		grid->SetCellValue(i, 1, wxString::Format("%d", selectedProducts[i].GetQuantity()));
		grid->SetCellValue(i, 2, wxString::Format("%d", selectedProducts[i].GetPrice()));
		int total = selectedProducts[i].GetQuantity() * selectedProducts[i].GetPrice();
		grid->SetCellValue(i, 3, wxString::Format("%d", total));
	}
}