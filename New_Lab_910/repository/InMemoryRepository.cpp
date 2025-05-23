#include "InMemoryRepository.h"

void repository::InMemoryRepository::add(std::shared_ptr<domain::Product> element) {
    validator->validate(*element);
    if (products.find(element->getId()) != products.end()) {
        throw ProductAlreadyExistsException("Product already exists");
    }
    products.insert(std::make_pair(element->getId(), element));
}

void repository::InMemoryRepository::remove(const std::string &key) {
    if (!products.count(key)) {
        throw ProductNotFoundException("Product not found");
    }
    products.erase(key);
}

void repository::InMemoryRepository::update(const std::string &key, std::shared_ptr<domain::Product> element) {
    validator->validate(*element);
    if (!products.count(key)) {
        throw ProductNotFoundException("Product not found");
    }
    products[key] = element;
}

std::vector<std::shared_ptr<domain::Product>> repository::InMemoryRepository::getAll() const {
    std::vector<std::shared_ptr<domain::Product>> result;
    for (auto &item : products) {
        result.push_back(item.second);
    }
    return result;
}

std::shared_ptr<domain::Product> repository::InMemoryRepository::findById(const std::string &key) const {
    auto it = products.find(key);
    return it != products.end() ? it->second : nullptr;
}
