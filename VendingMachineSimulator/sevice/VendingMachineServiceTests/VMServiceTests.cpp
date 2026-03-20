//
// Created by cipri on 5/17/2025.
//
#include <cassert>
#include <memory>
#include <iostream>
#include "../VendingMachineService.h"
#include "../../repository/InMemoryRepository.h"
#include "../../domain/ProductValidators.h"
#include "../../domain/GenericProduct.h"
#include "../../repository/RepositoryException.h"
#include "VMServiceTests.h"

void testGetAllProducts() {
    auto validator = std::make_shared<domain::GenericProductValidator>();
    std::shared_ptr<repository::Repository<domain::Product>> repo = std::make_shared<repository::InMemoryRepository>(validator);
    service::VendingMachineService service(repo);

    auto p1 = std::make_shared<domain::GenericProduct>("A1", "Chips", 5);
    auto p2 = std::make_shared<domain::GenericProduct>("B2", "Soda", 10);

    service.restockProduct(p1);
    service.restockProduct(p2);

    auto allProducts = service.getAllProducts();
    assert(allProducts.size() == 2);
}

void testBuyProductSuccess() {
    auto validator = std::make_shared<domain::GenericProductValidator>();
    std::shared_ptr<repository::Repository<domain::Product>> repo = std::make_shared<repository::InMemoryRepository>(validator);
    service::VendingMachineService service(repo);

    auto product = std::make_shared<domain::GenericProduct>("C3", "Juice", 15);
    service.restockProduct(product);

    service.buyProduct("C3");
    assert(service.getAllProducts().empty());
}

void testBuyProductNotFound() {
    auto validator = std::make_shared<domain::GenericProductValidator>();
    std::shared_ptr<repository::Repository<domain::Product>> repo = std::make_shared<repository::InMemoryRepository>(validator);
    service::VendingMachineService service(repo);

    bool exceptionThrown = false;
    try {
        service.buyProduct("Z9");
    } catch (const repository::ProductNotFoundException& e) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}

void testRestockProductDuplicate() {
    auto validator = std::make_shared<domain::GenericProductValidator>();
    std::shared_ptr<repository::Repository<domain::Product>> repo = std::make_shared<repository::InMemoryRepository>(validator);
    service::VendingMachineService service(repo);

    auto product = std::make_shared<domain::GenericProduct>("D4", "Candy", 3);
    service.restockProduct(product);

    bool exceptionThrown = false;
    try {
        service.restockProduct(product);
    } catch (const repository::ProductAlreadyExistsException& e) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}


void testGetProductById() {
    auto validator = std::make_shared<domain::GenericProductValidator>();
    std::shared_ptr<repository::Repository<domain::Product>> repo = std::make_shared<repository::InMemoryRepository>(validator);
    service::VendingMachineService service(repo);

    auto product = std::make_shared<domain::GenericProduct>("E5", "Water", 7);
    service.restockProduct(product);

    auto found = service.getProductById("E5");
    assert(found != nullptr);
    assert(found->getName() == "Water");

    auto notFound = service.getProductById("X1");
    assert(notFound == nullptr);
}

void testIsProductAvailable() {
    auto validator = std::make_shared<domain::GenericProductValidator>();
    std::shared_ptr<repository::Repository<domain::Product>> repo = std::make_shared<repository::InMemoryRepository>(validator);
    service::VendingMachineService service(repo);

    auto product = std::make_shared<domain::GenericProduct>("F6", "Chocolate", 8);
    service.restockProduct(product);

    assert(service.isProductAvailable("F6") == true);
    assert(service.isProductAvailable("Y2") == false);
}

void testGetProductPrice() {
    auto validator = std::make_shared<domain::GenericProductValidator>();
    std::shared_ptr<repository::Repository<domain::Product>> repo = std::make_shared<repository::InMemoryRepository>(validator);
    service::VendingMachineService service(repo);

    auto product = std::make_shared<domain::GenericProduct>("G7", "Gum", 2);
    service.restockProduct(product);

    assert(service.getProductPrice("G7") == 2);

    bool exceptionThrown = false;
    try {
        service.getProductPrice("Z9");
    } catch (const repository::ProductNotFoundException& e) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}

void testAllVMService() {
    testGetAllProducts();
    testBuyProductSuccess();
    testBuyProductNotFound();
    testRestockProductDuplicate();
    testGetProductPrice();
    testGetProductById();
    testIsProductAvailable();

}