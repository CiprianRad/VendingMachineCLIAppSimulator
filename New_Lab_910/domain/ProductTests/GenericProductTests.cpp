//
// Created by cipri on 5/17/2025.
//

#include <cassert>
#include <sstream>
#include <iostream>
#include "../GenericProduct.h"
#include "GenericProductTests.h"

void testGenericProductConstructorAndGetters() {
    domain::GenericProduct product("A1", "Cola", 150);
    assert(product.getId() == "A1");
    assert(product.getName() == "Cola");
    assert(product.getPrice() == 150);
}

void testGenericProductSetters() {
    domain::GenericProduct product("B2", "Water", 100);
    product.setName("Sparkling Water");
    product.setPrice(120);

    assert(product.getName() == "Sparkling Water");
    assert(product.getPrice() == 120);
}

void testGenericProductDefaultConstructor() {
    domain::GenericProduct product;
    assert(product.getId().empty());
    assert(product.getName().empty());
    assert(product.getPrice() == 0);
}

void testGenericProductStreamOutput() {
    domain::GenericProduct product("C3", "Juice", 200);
    std::ostringstream os;
    os << product;

    std::string output = os.str();
    assert(output.find("C3") != std::string::npos);
    assert(output.find("Juice") != std::string::npos);
    assert(output.find("200") != std::string::npos);
}

void testGenericProductStreamInput() {
    std::istringstream is("D4\nSoda\n250\n");
    domain::GenericProduct product;
    is >> product;

    assert(product.getId() == "D4");
    assert(product.getName() == "Soda");
    assert(product.getPrice() == 250);
}


void testAllProducts() {
    testGenericProductConstructorAndGetters();
    testGenericProductSetters();
    testGenericProductDefaultConstructor();
    testGenericProductStreamOutput();
    testGenericProductStreamInput();
}