//
// Created by cipri on 5/19/2025.
//
#include "VendingMachineControllerTests.h"

#include <fstream>
#include <cassert>
#include <memory>
#include <iostream>

// Helper functions to create and delete test files
void createTestProductsFile(const std::string& filename) {
    std::ofstream out(filename);
    out << "T1 Cola 6\n";
    out << "T2 Chips 5\n";
    out << "T3 Candy 4\n";
    out.close();
}

void createTestBanknotesFile(const std::string& filename) {
    std::ofstream out(filename);
    out << "5 5\n";   // 5-value banknotes, quantity 5
    out << "1 10\n";  // 1-value banknotes, quantity 10
    out.close();
}

void createInvalidBanknotesFile(const std::string& filename) {
    std::ofstream out(filename);
    out << "-1 5\n";  // Invalid negative denomination
    out.close();
}

void deleteFile(const std::string& filename) {
    std::remove(filename.c_str());
}

void createTestQuantitiesFile(const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Failed to create test quantities file: " + filename);
    }

    // Example test quantities
    out << "T1 5\n";
    out << "T2 3\n";
    out << "T3 0\n";

    out.close();
}


// void testLoadBanknotes() {
//     auto validator = std::make_shared<domain::GenericProductValidator>();
//     auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
//     auto service = std::make_shared<service::VendingMachineService>(repo);
//     controller::VendingMachineController controller(service, {}, "test_banknotes.txt");
//
//     auto banknotes = controller.getBanknotes();
//     assert(banknotes.size() == 2);
// }

// void testLoadBanknotes() {
//     const std::string banknotesFile = "test_banknotes.txt";
//     createTestBanknotesFile(banknotesFile);
//
//     auto validator = std::make_shared<domain::GenericProductValidator>();
//     createTestProductsFile("test_products.txt");
//     auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
//     auto service = std::make_shared<service::VendingMachineService>(repo);
//
//     controller::VendingMachineController controller(service, {}, banknotesFile);
//
//     auto banknotes = controller.getBanknotes();
//     assert(banknotes.size() == 2);
//
//     deleteFile(banknotesFile);
//     deleteFile("test_products.txt");
// }


void testLoadBanknotes() {
    const std::string banknotesFile = "test_banknotes.txt";
    const std::string quantitiesFile = "test_quantities.txt";
    const std::string productsFile = "test_products.txt";

    createTestBanknotesFile(banknotesFile);
    createTestQuantitiesFile(quantitiesFile);
    createTestProductsFile(productsFile);

    auto validator = std::make_shared<domain::GenericProductValidator>();
    auto repo = std::make_shared<repository::FileRepository>(productsFile, validator);
    auto service = std::make_shared<service::VendingMachineService>(repo);

    controller::VendingMachineController controller(service, {}, banknotesFile, quantitiesFile);

    auto banknotes = controller.getBanknotes();
    assert(banknotes.size() == 2);
    assert(banknotes[0].first == 5);  // denomination
    assert(banknotes[0].second == 5); // quantity

    deleteFile(banknotesFile);
    deleteFile(quantitiesFile);
    deleteFile(productsFile);
}



//
// void testSetProductQuantity() {
//     auto validator = std::make_shared<domain::GenericProductValidator>();
//     auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
//     auto service = std::make_shared<service::VendingMachineService>(repo);
//     controller::VendingMachineController controller(service, {}, "test_banknotes.txt");
//
//     controller.setProductQuantity("T1", 2);
//     assert(controller.getProductQuantity("T1") == 2);
//
//     try {
//         controller.setProductQuantity("T2", -1);
//         assert(false);
//     } catch (const controller::NegativeQuantitySetException&) {
//         assert(true);
//     }
// }

void testSetAndGetProductQuantity() {
    createTestProductsFile("test_products.txt");
    createTestBanknotesFile("test_banknotes.txt");
    createTestQuantitiesFile("test_quantities.txt");

    auto validator = std::make_shared<domain::GenericProductValidator>();
    auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
    auto service = std::make_shared<service::VendingMachineService>(repo);

    controller::VendingMachineController controller(service, {}, "test_banknotes.txt", "test_quantities.txt");

    controller.setProductQuantity("T1", 5);
    assert(controller.getProductQuantity("T1") == 5);

    try {
        controller.setProductQuantity("T2", -1);
        assert(false);  // Should throw, so fail if we reach here
    } catch (const controller::NegativeQuantitySetException&) {
        assert(true);
    }

    deleteFile("test_products.txt");
    deleteFile("test_banknotes.txt");
    deleteFile("test_quantities.txt");
}


// void testSetAndGetProductQuantity() {
//     createTestProductsFile("test_products.txt");
//     createTestBanknotesFile("test_banknotes.txt");
//
//     auto validator = std::make_shared<domain::GenericProductValidator>();
//     auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
//     auto service = std::make_shared<service::VendingMachineService>(repo);
//
//     controller::VendingMachineController controller(service, {}, "test_banknotes.txt");
//
//     controller.setProductQuantity("T1", 5);
//     assert(controller.getProductQuantity("T1") == 5);
//
//     try {
//         controller.setProductQuantity("T2", -1);
//         assert(false);  // Should throw, so fail if we reach here
//     } catch (const controller::NegativeQuantitySetException&) {
//         assert(true);
//     }
//
//     deleteFile("test_products.txt");
//     deleteFile("test_banknotes.txt");
// }




// void testRestockProduct() {
//     auto validator = std::make_shared<domain::GenericProductValidator>();
//     auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
//     auto service = std::make_shared<service::VendingMachineService>(repo);
//     controller::VendingMachineController controller(service, {}, "test_banknotes.txt");
//
//     auto product = std::make_shared<domain::GenericProduct>("T1", "Cola", 6);
//     controller.restockProduct(product, 3);
//     assert(controller.getProductQuantity("T1") == 3);
//
//     try {
//         controller.restockProduct(product, 0);
//         assert(false);
//     } catch (const controller::InvalidQuantityException&) {
//         assert(true);
//     }
// }
//
// void testBuyProductSuccessAndChange() {
//     auto validator = std::make_shared<domain::GenericProductValidator>();
//     auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
//     auto service = std::make_shared<service::VendingMachineService>(repo);
//     controller::VendingMachineController controller(service, {{"T1", 1}}, "test_banknotes.txt");
//
//     auto change = controller.buyProduct("T1", 10);
//     assert(!change.empty());
//     assert(controller.getProductQuantity("T1") == 0);
// }
//
// void testOutOfStock() {
//     auto validator = std::make_shared<domain::GenericProductValidator>();
//     auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
//     auto service = std::make_shared<service::VendingMachineService>(repo);
//     controller::VendingMachineController controller(service, {{"T3", 0}}, "test_banknotes.txt");
//
//     try {
//         controller.buyProduct("T3", 5);
//         assert(false);
//     } catch (const controller::OutOfStockException&) {
//         assert(true);
//     }
// }
//
// void testProductUnavailable() {
//     auto validator = std::make_shared<domain::GenericProductValidator>();
//     auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
//     repo->remove("T2");
//
//     auto service = std::make_shared<service::VendingMachineService>(repo);
//     controller::VendingMachineController controller(service, {{"T2", 1}}, "test_banknotes.txt");
//
//     try {
//         controller.buyProduct("T2", 10);
//         assert(false);
//     } catch (const controller::ProductUnavailableException&) {
//         assert(true);
//     }
// }
//
// void testInsufficientPayment() {
//     auto validator = std::make_shared<domain::GenericProductValidator>();
//     auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
//     auto service = std::make_shared<service::VendingMachineService>(repo);
//     controller::VendingMachineController controller(service, {{"T1", 1}}, "test_banknotes.txt");
//
//     try {
//         controller.buyProduct("T1", 1);
//         assert(false);
//     } catch (const controller::InsufficientPaymentException&) {
//         assert(true);
//     }
// }
//
// void testInvalidBanknotesFile() {
//     auto validator = std::make_shared<domain::GenericProductValidator>();
//     auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
//     auto service = std::make_shared<service::VendingMachineService>(repo);
//
//     try {
//         controller::VendingMachineController controller(service, {}, "test_invalid_banknotes.txt");
//         assert(false);
//     } catch (const controller::InvalidBanknoteFormatException&) {
//         assert(true);
//     }
// }


// void testRestockProduct() {
//     createTestProductsFile("test_products.txt");
//     createTestBanknotesFile("test_banknotes.txt");
//
//     auto validator = std::make_shared<domain::GenericProductValidator>();
//     auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
//     auto service = std::make_shared<service::VendingMachineService>(repo);
//
//     controller::VendingMachineController controller(service, { {"T1", 2} }, "test_banknotes.txt");
//
//     auto product = std::make_shared<domain::GenericProduct>("T1", "Cola", 6);
//
//     controller.restockProduct(product, 3);
//     assert(controller.getProductQuantity("T1") == 5);
//
//     try {
//         controller.restockProduct(product, 0);
//         assert(false);
//     } catch (const controller::InvalidQuantityException&) {
//         assert(true);
//     }
//
//     deleteFile("test_products.txt");
//     deleteFile("test_banknotes.txt");
// }

void testRestockProduct() {
    createTestProductsFile("test_products.txt");
    createTestBanknotesFile("test_banknotes.txt");
    createTestQuantitiesFile("test_quantities.txt");

    auto validator = std::make_shared<domain::GenericProductValidator>();
    auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
    auto service = std::make_shared<service::VendingMachineService>(repo);

    controller::VendingMachineController controller(service, { {"T1", 2} }, "test_banknotes.txt", "test_quantities.txt");

    auto product = std::make_shared<domain::GenericProduct>("T1", "Cola", 6);

    controller.restockProduct(product, 3);
    assert(controller.getProductQuantity("T1") == 8);

    try {
        controller.restockProduct(product, 0);
        assert(false);
    } catch (const controller::InvalidQuantityException&) {
        assert(true);
    }

    deleteFile("test_products.txt");
    deleteFile("test_banknotes.txt");
    deleteFile("test_quantities.txt");
}


// void testBuyProductAndExceptions() {
//     createTestProductsFile("test_products.txt");
//     createTestBanknotesFile("test_banknotes.txt");
//
//     auto validator = std::make_shared<domain::GenericProductValidator>();
//     auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
//     auto service = std::make_shared<service::VendingMachineService>(repo);
//
//     controller::VendingMachineController controller(service, { {"T1", 2}, {"T3", 0}, {"T2", 1} }, "test_banknotes.txt");
//
//     // Successful purchase
//     auto change = controller.buyProduct("T1", 10);
//     assert(!change.empty());
//     assert(controller.getProductQuantity("T1") == 1);
//
//     // Out of stock exception
//     try {
//         controller.buyProduct("T3", 5);
//         assert(false);
//     } catch (const controller::OutOfStockException&) {
//         assert(true);
//     }
//
//     // Product unavailable exception (simulate by removing from repo)
//     repo->remove("T2");
//     try {
//         controller.buyProduct("T2", 10);
//         assert(false);
//     } catch (const controller::ProductUnavailableException&) {
//         assert(true);
//     }
//
//     // Insufficient payment exception
//     controller.setProductQuantity("T1", 1);
//     try {
//         controller.buyProduct("T1", 1);  // price is 6, paid less
//         assert(false);
//     } catch (const controller::InsufficientPaymentException&) {
//         assert(true);
//     }
//
//     deleteFile("test_products.txt");
//     deleteFile("test_banknotes.txt");
// }

void testBuyProductAndExceptions() {
    createTestProductsFile("test_products.txt");
    createTestBanknotesFile("test_banknotes.txt");
    createTestQuantitiesFile("test_quantities.txt");

    auto validator = std::make_shared<domain::GenericProductValidator>();
    auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
    auto service = std::make_shared<service::VendingMachineService>(repo);

    // Don't pass an inventory map – it's overridden anyway
    controller::VendingMachineController controller(service, {}, "test_banknotes.txt", "test_quantities.txt");

    // T1 has 5 in quantities file; after one purchase, it should have 4
    auto change = controller.buyProduct("T1", 10);
    assert(!change.empty());
    assert(controller.getProductQuantity("T1") == 4);

    // T3 has 0 in quantities file
    try {
        controller.buyProduct("T3", 5);
        assert(false);
    } catch (const controller::OutOfStockException&) {
        assert(true);
    }

    // Remove T2 from the repo
    repo->remove("T2");
    try {
        controller.buyProduct("T2", 10);
        assert(false);
    } catch (const controller::ProductUnavailableException&) {
        assert(true);
    }

    // T1 price is 6; this should throw for insufficient payment
    controller.setProductQuantity("T1", 1);
    try {
        controller.buyProduct("T1", 1);  // Price is 6, paid only 1
        assert(false);
    } catch (const controller::InsufficientPaymentException&) {
        assert(true);
    }

    deleteFile("test_products.txt");
    deleteFile("test_banknotes.txt");
    deleteFile("test_quantities.txt");
}


// void testInvalidBanknotesFile() {
//     const std::string invalidFile = "test_invalid_banknotes.txt";
//     createInvalidBanknotesFile(invalidFile);
//
//     auto validator = std::make_shared<domain::GenericProductValidator>();
//     createTestProductsFile("test_products.txt");
//     auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
//     auto service = std::make_shared<service::VendingMachineService>(repo);
//
//     try {
//         controller::VendingMachineController controller(service, {}, invalidFile);
//         assert(false);  // Should throw
//     } catch (const controller::InvalidBanknoteFormatException&) {
//         assert(true);
//     }
//
//     deleteFile(invalidFile);
//     deleteFile("test_products.txt");
// }

void testInvalidBanknotesFile() {
    const std::string invalidFile = "test_invalid_banknotes.txt";

    createInvalidBanknotesFile(invalidFile);
    createTestProductsFile("test_products.txt");
    createTestQuantitiesFile("test_quantities.txt");

    auto validator = std::make_shared<domain::GenericProductValidator>();
    auto repo = std::make_shared<repository::FileRepository>("test_products.txt", validator);
    auto service = std::make_shared<service::VendingMachineService>(repo);

    try {
        controller::VendingMachineController controller(service, {}, invalidFile, "test_quantities.txt");
        assert(false);  // Should throw
    } catch (const controller::InvalidBanknoteFormatException&) {
        assert(true);
    }

    deleteFile(invalidFile);
    deleteFile("test_products.txt");
    deleteFile("test_quantities.txt");
}





void runAllControllerTests() {
    testLoadBanknotes();
    std::cout << "Passed1";
    testSetAndGetProductQuantity();
    std::cout << "Passed1";
    testRestockProduct();
    std::cout << "Passed1";
    testBuyProductAndExceptions();
    std::cout << "Passed1";
    testInvalidBanknotesFile();
    std::cout << "Passed1";
}

