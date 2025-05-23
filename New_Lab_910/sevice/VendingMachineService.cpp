//
// Created by cipri on 5/17/2025.
//

#include "VendingMachineService.h"

#include "../repository/RepositoryException.h"

std::vector<std::shared_ptr<domain::Product>> service::VendingMachineService::getAllProducts() {
    return repository->getAll();
}

std::shared_ptr<domain::Product> service::VendingMachineService::getProductById(const std::string &productId) {
    return repository->findById(productId);
}

void service::VendingMachineService::buyProduct(const std::string& productId) {
    std::shared_ptr<domain::Product> product;
    product = repository->findById(productId);
    if (product == nullptr) {
        throw repository::ProductNotFoundException("Product no longer in stock");
    }
    repository->remove(productId);
}

void service::VendingMachineService::restockProduct(std::shared_ptr<domain::Product> product) {
    repository->add(product);
}

bool service::VendingMachineService::isProductAvailable(const std::string &productId) {
    std::shared_ptr<domain::Product> product = repository->findById(productId);
    if (product == nullptr) {
        return false;
    }
    return true;
}

int service::VendingMachineService::getProductPrice(const std::string &productId) {
    std::shared_ptr<domain::Product> product = repository->findById(productId);
    if (product == nullptr) {
        throw repository::ProductNotFoundException("Product not found");
    }
    return product->getPrice();
}

