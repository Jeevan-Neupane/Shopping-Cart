#pragma once
#include <wx/wx.h>
#include "Product.h"
#include <wx/grid.h>

class SelectedItemsFrame : public wxFrame {
public:
	SelectedItemsFrame(const std::vector<Product>& selectedProducts);

private:
	wxGrid* grid;

	void UpdateGrid(const std::vector<Product>& selectedProducts);
};