// Product.cpp
#include "Product.h"

Product::Product() : isSelected_(0), price_(0), quantity_(0) {}

Product::Product(int isSelected, const std::string& name, int price, int quantity)
    : isSelected_(isSelected), name_(name), price_(price), quantity_(quantity) {}

int Product::GetIsSelected() const { return isSelected_; }
void Product::SetIsSelected(int isSelected) { isSelected_ = isSelected; }

std::string Product::GetName() const { return name_; }
int Product::GetPrice() const { return price_; }
int Product::GetQuantity() const { return quantity_; }
void Product::SetQuantity(int quantity) { quantity_ = quantity; }
