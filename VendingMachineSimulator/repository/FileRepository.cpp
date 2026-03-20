//
// Created by cipri on 5/17/2025.
//
#include "FileRepository.h"



repository::FileRepository::FileRepository(const std::string &fileName, std::shared_ptr<domain::ProductValidator> validator)
        : repository::InMemoryRepository(validator), fileName(fileName), validator(std::move(validator)) {
    loadData();
}

void repository::FileRepository::loadData() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw FileRepositoryException("File Not Found");
    }

    std::string id, name;
    int price;
    std::string line;

    isLoading = true;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (!(iss >> id >> name >> price)) {
            throw InvalidLineFormatException("Invalid line format: " + line);
        }

        auto product = std::make_shared<domain::GenericProduct>(id, name, price);
        validator->validate(*product);
        InMemoryRepository::add(product);
    }
    isLoading = false;
}

void repository::FileRepository::saveData() {
    if (isLoading) return;

    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw FileRepositoryException("File Not Found");
    }

    for (const auto& product : getAll()) {
        file << product->getId() << " " << product->getName() << " " << product->getPrice() << "\n";
    }
}



void repository::FileRepository::add(std::shared_ptr<domain::Product> product) {
    InMemoryRepository::add(product);
    saveData();
}

void repository::FileRepository::update(const std::string &key, std::shared_ptr<domain::Product> product) {
    InMemoryRepository::update(key, product);
    saveData();
}

void repository::FileRepository::remove(const std::string &key) {
    InMemoryRepository::remove(key);
    saveData();
}

std::vector<std::shared_ptr<domain::Product>> repository::FileRepository::getAll() const {
    return InMemoryRepository::getAll();
}

std::shared_ptr<domain::Product> repository::FileRepository::findById(const std::string &key) const {
    return InMemoryRepository::findById(key);
}

