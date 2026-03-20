//
// Created by cipri on 5/19/2025.
//

#ifndef VENDINGMACHINECONTROLLERTESTS_H
#define VENDINGMACHINECONTROLLERTESTS_H
#include <cassert>
#include <string>
#include <memory>
#include "../../domain/GenericProduct.h"
#include "../../domain/ProductValidators.h"
#include "../../repository/FileRepository.h"
#include "../../controller/VendingMachineController.h"

void testLoadBanknotes();
// void testSetProductQuantity();
// void testRestockProduct();
// void testBuyProductSuccessAndChange();
// void testOutOfStock();
// void testProductUnavailable();
// void testInsufficientPayment();
// void testInvalidBanknotesFile();
// void runAllControllerTests();
void createTestProductsFile(const std::string& filename);
void createTestBanknotesFile(const std::string& filename);
void createInvalidBanknotesFile(const std::string& filename);
void deleteFile(const std::string& filename);
void testSetAndGetProductQuantity();
void testRestockProduct();
void testBuyProductAndExceptions();
void testInvalidBanknotesFile();
void runAllControllerTests();
void createTestQuantitiesFile(const std::string& filename);

#endif //VENDINGMACHINECONTROLLERTESTS_H
