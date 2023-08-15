#include "AdminAddedProduct.h"


AdminAddedProducts::AdminAddedProducts(const wxString& name, double price, int rating, const wxString& description, int quantity)
    : name(name), price(price), rating(rating), description(description), quantity(quantity) {}

wxString AdminAddedProducts::GetName() const { return name; }
double AdminAddedProducts::GetPrice() const { return price; }
int AdminAddedProducts::GetRating() const { return rating; }
wxString AdminAddedProducts::GetDescription() const { return description; }
int AdminAddedProducts::GetQuantity() const { return quantity; }
