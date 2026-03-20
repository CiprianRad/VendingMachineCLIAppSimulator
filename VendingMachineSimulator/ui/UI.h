//
// Created by cipri on 5/19/2025.
//

#ifndef UI_H
#define UI_H
#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include "../controller/VendingMachineController.h"


#include <iostream>
#include <memory>
#include <limits>
#include "../controller/VendingMachineController.h"

namespace ui {
    class VendingMachineUI {
    private:
        std::shared_ptr<controller::VendingMachineController> controller;
        int virtualBalance = 0;

        void displayMenu() const {
            std::cout << "\n=== Vending Machine ===\n";
            std::cout << "1. View products\n";
            std::cout << "2. Deposit money\n";
            std::cout << "3. Buy product\n";
            std::cout << "4. Get change\n";
            std::cout << "0. Exit\n";
        }

        void viewProducts() const {
            auto products = controller->getService()->getAllProducts();
            std::cout << "\nAvailable products:\n";
            for (const auto& product : products) {
                std::cout << product->getId() << " - " << product->getName()
                          << " | Price: " << product->getPrice()
                          << " | Quantity: " << controller->getProductQuantity(product->getId()) << "\n";
            }
        }

        void depositMoney() {
            std::cout << "Enter amount to deposit: ";
            int amount;
            std::cin >> amount;

            if (amount <= 0) {
                std::cout << "Invalid amount.\n";
                return;
            }

            try {
                controller->addBanknotes(amount);  // Machine receives the cash
                virtualBalance += amount;          // User’s virtual credit
                std::cout << "Balance updated. Current balance: " << virtualBalance << "\n";
            } catch (const std::exception& e) {
                std::cout << "Failed to deposit money: " << e.what() << "\n";
            }
        }

        void buyProduct() {
            std::string productId;
            std::cout << "Enter product ID to buy: ";
            std::cin >> productId;

            auto product = controller->getService()->getProductById(productId);
            if (!product) {
                std::cout << "Product not found.\n";
                return;
            }

            int price = product->getPrice();
            if (virtualBalance < price) {
                std::cout << "Insufficient balance. Product costs " << price
                          << ", current balance is " << virtualBalance << "\n";
                return;
            }

            try {
                auto change = controller->buyProduct(productId, virtualBalance);
                std::cout << "Product purchased successfully.\n";

                if (!change.empty()) {
                    std::cout << "Change returned:\n";
                    for (const auto& [note, count] : change)
                        std::cout << count << " x " << note << "\n";
                }

                virtualBalance = 0;
            } catch (const std::exception& e) {
                std::cout << "Purchase failed: " << e.what() << "\n";
            }
        }

        void getChange() {
            if (virtualBalance == 0) {
                std::cout << "No balance to return.\n";
                return;
            }

            try {
                auto change = controller->calculateChange(virtualBalance);
                if (change.empty()) {
                    std::cout << "Unable to return change. Please try buying a product instead.\n";
                    return;
                }

                controller->removeBanknotes(change);
                std::cout << "Returning change:\n";
                for (const auto& [note, count] : change)
                    std::cout << count << " x " << note << "\n";

                virtualBalance = 0;
            } catch (const std::exception& e) {
                std::cout << "Error while returning change: " << e.what() << "\n";
            }
        }

        // Optional: call this if you want to implement saving inventory/banknotes later
        void saveState() {
            // Placeholder: implement if needed
        }

    public:
        explicit VendingMachineUI(std::shared_ptr<controller::VendingMachineController> ctrl)
            : controller(std::move(ctrl)) {}

        void run() {
            std::cout << "Vending Machine loaded successfully.\n";

            int option;
            do {
                displayMenu();
                std::cout << "Option: ";
                std::cin >> option;

                switch (option) {
                    case 1: viewProducts(); break;
                    case 2: depositMoney(); break;
                    case 3: buyProduct(); break;
                    case 4: getChange(); break;
                    case 0:
                        std::cout << "Exiting. Goodbye!\n";
                        getChange();  // Auto-return any remaining balance
                        saveState();  // Optional: stub
                        break;
                    default:
                        std::cout << "Invalid option. Try again.\n";
                }
            } while (option != 0);
        }
    };
}


#endif //UI_H
