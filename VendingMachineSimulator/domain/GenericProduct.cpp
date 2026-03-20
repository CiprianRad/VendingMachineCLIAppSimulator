//
// Created by cipri on 5/16/2025.
//
#include "GenericProduct.h"

domain::GenericProduct::GenericProduct() {
    this->id = "";
    this->name = "";
    this->price = 0;
}

domain::GenericProduct::GenericProduct(const std::string &id, const std::string &name, int price) {
    this->id = id;
    this->name = name;
    this->price = price;
}

std::string domain::GenericProduct::getId() const {
    return this->id;
}

std::string domain::GenericProduct::getName() const {
    return this->name;
}

int domain::GenericProduct::getPrice() const {
    return this->price;
}

void domain::GenericProduct::setPrice(const int &value) {
    this->price = value;
}

void domain::GenericProduct::setName(const std::string &value) {
    this->name = value;
}



namespace domain {
    std::ostream& operator<<(std::ostream& os, const domain::GenericProduct& product) {
        os << product.getId() << "\n"
           << product.getName() << "\n"
           << product.getPrice() << "\n";
        return os;
    }

    std::istream& operator>>(std::istream& is, domain::GenericProduct& product) {
        std::string id;
        std::string name;
        int price;

        std::getline(is, id);
        std::getline(is, name);
        is >> price;
        is.ignore();

        product = domain::GenericProduct(id, name, price);
        return is;
    }
}

