#pragma once
#include <wx/wx.h>

class AdminAddedProducts
{
public:
    AdminAddedProducts(const wxString& name, double price, int rating, const wxString& description, int quantity);

    wxString GetName() const;
    double GetPrice() const;
    int GetRating() const;
    wxString GetDescription() const;
    int GetQuantity() const;

private:
    wxString name;
    double price;
    int rating;
    wxString description;
    int quantity;
};