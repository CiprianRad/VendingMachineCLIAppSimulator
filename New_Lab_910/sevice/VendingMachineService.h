//
// Created by cipri on 5/17/2025.
//

#ifndef VENDINGMACHINESERVICE_H
#define VENDINGMACHINESERVICE_H
#include <memory>
#include "../repository/Repository.h"
#include "../domain/Product.h"
#include <vector>
#include <algorithm>
namespace service {
    class VendingMachineService {
    private:
        std::shared_ptr<repository::Repository<domain::Product>> repository;
    public:
        explicit VendingMachineService(std::shared_ptr<repository::Repository<domain::Product>> repository) :  repository(std::move(repository)) {}
        std::vector<std::shared_ptr<domain::Product>> getAllProducts();
        std::shared_ptr<domain::Product> getProductById(const std::string& productId);
        void buyProduct(const std::string& productId);
        void restockProduct(std::shared_ptr<domain::Product> product);
        bool isProductAvailable(const std::string& productId);
        int getProductPrice(const std::string& productId);

    };
}


#endif //VENDINGMACHINESERVICE_H
