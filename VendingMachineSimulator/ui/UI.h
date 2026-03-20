//
// Created by cipri on 5/19/2025.
//

#ifndef UI_H
#define UI_H

#include <memory>
#include <string>
#include "../controller/VendingMachineController.h"

namespace ui {
    class VendingMachineUI {
    private:
        std::shared_ptr<controller::VendingMachineController> controller;
        int virtualBalance = 0;

        void displayMenu() const;
        void viewProducts() const;
        void depositMoney();
        void buyProduct();
        void getChange();
        void saveState();

    public:
        explicit VendingMachineUI(std::shared_ptr<controller::VendingMachineController> ctrl);
        void run();
    };
}

#endif // UI_H
