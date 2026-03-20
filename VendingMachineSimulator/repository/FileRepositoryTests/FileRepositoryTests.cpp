//
// Created by cipri on 5/17/2025.
//
#include "FIleRepositoryTests.h"
#include <cassert>
#include <fstream>
#include <memory>
#include "../FileRepositoryException.h"
#include "../FileRepository.h"
#include "../../domain/ProductValidators.h"
#include "../../domain/GenericProduct.h"

void createTestFile(const std::string& filename) {
    std::ofstream file(filename);
    file << "T1 Cola 6\n";
    file << "T2 Chips 5\n";
    file << "T3 Candy 3\n";
    file.close();
}

void deleteTestFile(const std::string& filename) {
    std::remove(filename.c_str());
}

void testFileRepository() {
    const std::string filename = "test_products.txt";
    createTestFile(filename);

    auto validator = std::make_shared<domain::GenericProductValidator>();
    std::cout << "ok";
    repository::FileRepository repo(filename, validator);

    std::cout << "ok";
    auto all = repo.getAll();
    std::cout << "ok";
    assert(all.size() == 3);
    assert(repo.findById("T1")->getName() == "Cola");
    assert(repo.findById("T2")->getPrice() == 5);

    auto newProduct = std::make_shared<domain::GenericProduct>("T4", "Juice", 7);
    repo.add(newProduct);
    assert(repo.findById("T4")->getName() == "Juice");

    auto updatedProduct = std::make_shared<domain::GenericProduct>("T2", "PotatoChips", 6);
    repo.update("T2", updatedProduct);
    assert(repo.findById("T2")->getName() == "PotatoChips");
    assert(repo.findById("T2")->getPrice() == 6);

    repo.remove("T1");
    assert(repo.findById("T1") == nullptr);

    deleteTestFile(filename);
    std::cout << "All FileRepository tests passed.\n";
}