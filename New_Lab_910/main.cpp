#include <iostream>
#include "domain/GenericProduct.h"
#include "repository/InMemoryRepository.h"
#include "domain/ProductTests/GenericProductTests.h"
#include "repository/RepositoryTests/InMemoryRepositoryTests.h"
#include "repository/FileRepository.h"
#include "repository/FileRepositoryTests/FIleRepositoryTests.h"
#include "sevice/VendingMachineServiceTests/VMServiceTests.h"
#include "controller/VMControllerTests/VendingMachineControllerTests.h"
#include "ui/UI.h"

int main() {
    testAllProducts();
    testAllRepositoryTests();
    testFileRepository();
    testAllVMService();
    std::cout << "ok"<< std::endl;
    runAllControllerTests();
    std::cout << "ok"<< std::endl;
    domain::GenericProduct product;
    product.setName("sweet");
    product.setPrice(10);
    domain::GenericProduct product2 = domain::GenericProduct("12x4d", "name", 10);
    std::cout << "Hello, World!" << std::endl;
    std::cout << product.getName() << std::endl;
    std::cout << product.getPrice() << std::endl;
    std::cout << product2.getName() << std::endl;
    std::cout << product2.getPrice() << std::endl;
    try {
        // Initialize validator
        auto validator = std::make_shared<domain::GenericProductValidator>();


        // Create repository with validator and product file
        auto productRepo = std::make_shared<repository::FileRepository>(
            "products.txt", validator
        );

        // Create service with the repository
        auto service = std::make_shared<service::VendingMachineService>(productRepo);

        // Empty inventory, will be loaded from file in controller
        std::unordered_map<std::string, int> initialInventory;

        // Create controller with service, inventory, banknotes file and quantities file
        auto controller = std::make_shared<controller::VendingMachineController>(
            service,
            initialInventory,
            "banknotes.txt",
            "quantities.txt"
        );

        // Start the UI
        ui::VendingMachineUI ui(controller);
        ui.run();

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }




    return 0;
}