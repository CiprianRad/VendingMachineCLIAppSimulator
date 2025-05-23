//
// Created by cipri on 5/17/2025.
//

#ifndef VENDINGMACHINECONTROLLER_H
#define VENDINGMACHINECONTROLLER_H

#include <memory>
#include <unordered_map>
#include <utility>
#include "../repository/RepositoryException.h"
#include "../sevice/VendingMachineService.h"
#include <fstream>
#include "VMControllerExceptions.h"

namespace controller {
    class VendingMachineController {
    private:
        std::shared_ptr<service::VendingMachineService> service;
        std::vector<std::pair<int, int>> banknotes;
        std::unordered_map<std::string, int> inventory;
        std::string banknotesFileName;
        std::string productsFileName;
        void loadBanknotes();
        void loadProductQuantities();

    public:

        VendingMachineController(
    std::shared_ptr<service::VendingMachineService> service,
    const std::unordered_map<std::string, int>& inventory,
    const std::string& banknotesFile, const std::string& productsFile) : service(std::move(service)), inventory(inventory), banknotesFileName(banknotesFile), productsFileName(productsFile)
        {
            loadProductQuantities();
            loadBanknotes();
        }
        int getProductQuantity(const std::string& productId) const;
        void restockProduct(std::shared_ptr<domain::Product> product, int quantity);
        std::vector<std::pair<int, int>> buyProduct(const std::string& productId, int paidAmount);
        void addBanknotes(int amount);
        void removeBanknotes(const std::vector<std::pair<int, int>>& change);
        std::vector<std::pair<int, int>> calculateChange(int changeAmount) const;
        std::vector<std::pair<int, int>> getBanknotes() const;
        void setProductQuantity(const std::string& productId, int quantity);

        std::shared_ptr<service::VendingMachineService> getService() const;
    };
}



#endif //VENDINGMACHINECONTROLLER_H
