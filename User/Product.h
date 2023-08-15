// Product.h
#pragma once

#include <string>

class Product {
public:
    Product();
    Product(int isSelected, const std::string& name, int price, int quantity);

    int GetIsSelected() const;
    void SetIsSelected(int isSelected);

    std::string GetName() const;
    int GetPrice() const;
    int GetQuantity() const;
    void SetQuantity(int quantity);

private:
    int isSelected_;
    std::string name_;
    int price_;
    int quantity_;
};
