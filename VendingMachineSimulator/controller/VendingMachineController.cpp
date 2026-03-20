//
// Created by cipri on 5/17/2025.
//

#include "VendingMachineController.h"


void controller::VendingMachineController::loadBanknotes() {
    std::ifstream file(banknotesFileName);
    if (!file.is_open()) {
        throw FileOpenException(banknotesFileName);
    }

    int value, quantity;
    while (file >> value >> quantity) {
        if (value <= 0 || quantity < 0) {
            throw InvalidBanknoteFormatException();
        }

        banknotes.emplace_back(value, quantity);
    }

    file.close();

}


void controller::VendingMachineController::loadProductQuantities() {
    std::ifstream file(productsFileName);
    if (!file.is_open()) {
        throw FileOpenException(productsFileName);
    }

    std::string productId;
    int quantity;

    while (file >> productId >> quantity) {
        if (quantity < 0) {
            throw InvalidQuantityException();
        }
        inventory[productId] = quantity;
    }

    file.close();
}


int controller::VendingMachineController::getProductQuantity(const std::string& productId) const {
        auto it = inventory.find(productId);
        return (it != inventory.end()) ? it->second : 0;
    }

void controller::VendingMachineController::restockProduct(std::shared_ptr<domain::Product> product, int quantity) {
    if (quantity <= 0) {
        throw InvalidQuantityException();
    }

    try {
        service->restockProduct(product);
    } catch (const repository::ProductAlreadyExistsException&) {

    }
    inventory[product->getId()] += quantity;
}

// Buy product by id and pay amount
// Returns change to give back to the customer as vector of pairs <denomination, quantity>
std::vector<std::pair<int, int>> controller::VendingMachineController::buyProduct(const std::string& productId, int paidAmount) {
    int quantity = getProductQuantity(productId);
    if (quantity <= 0) {
        throw OutOfStockException(productId);
    }

    if (!service->isProductAvailable(productId)) {
        throw ProductUnavailableException(productId);
    }

    int price = service->getProductPrice(productId);
    if (paidAmount < price) {
        throw InsufficientPaymentException(price, paidAmount);
    }

    int changeAmount = paidAmount - price;

    // Try to compute change from banknotes
    auto change = calculateChange(changeAmount);
    if (changeAmount > 0 && change.empty()) {
        throw ChangeUnavailableException();
    }

    // Update banknotes: add paidAmount in denominations, remove given change
    addBanknotes(paidAmount);
    removeBanknotes(change);

    // Update inventory
    inventory[productId] -= 1;
    if (inventory[productId] == 0) {
        // Remove product from service repository once quantity hits zero
        service->buyProduct(productId);
        inventory.erase(productId);
    }

    return change;
}

void controller::VendingMachineController::addBanknotes(int amount) {
    for (auto& [denom, qty] : banknotes) {
        if (denom == amount) {
            qty++;
            return;
        }
    }
    // If denomination not found, add new
    banknotes.emplace_back(amount, 1);
}

// Remove banknotes as change
void controller::VendingMachineController::removeBanknotes(const std::vector<std::pair<int, int>>& change) {
    for (const auto& [denom, qty] : change) {
        for (auto& [bDenom, bQty] : banknotes) {
            if (bDenom == denom) {
                if (bQty < qty) {
                    throw NotEnoughBanknotesException(denom);
                }
                bQty -= qty;
            }
        }
    }
}

// Calculate change vector (largest denominations first)
std::vector<std::pair<int, int>> controller::VendingMachineController::calculateChange(int changeAmount) const {
    std::vector<std::pair<int, int>> result;
    if (changeAmount == 0) return result;

    int remaining = changeAmount;

    // Sort banknotes descending by denomination
    std::vector<std::pair<int, int>> sortedBanknotes = banknotes;
    std::sort(sortedBanknotes.begin(), sortedBanknotes.end(),
              [](auto& a, auto& b) { return a.first > b.first; });

    for (auto& [denom, qty] : sortedBanknotes) {
        if (denom <= 0) continue;
        int needed = remaining / denom;
        int used = std::min(needed, qty);
        if (used > 0) {
            result.emplace_back(denom, used);
            remaining -= used * denom;
        }
        if (remaining == 0) break;
    }

    if (remaining != 0) {
        // Cannot provide exact change
        return {};
    }

    return result;
}

std::vector<std::pair<int, int>> controller::VendingMachineController::getBanknotes() const {
    return banknotes;
}

void controller::VendingMachineController::setProductQuantity(const std::string &productId, int quantity) {
    if (quantity < 0) {
        throw NegativeQuantitySetException();
    }
    inventory[productId] = quantity;
}

std::shared_ptr<service::VendingMachineService> controller::VendingMachineController::getService() const {
    return this->service;
}
