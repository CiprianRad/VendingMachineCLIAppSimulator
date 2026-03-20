//
// Created by cipri on 5/17/2025.
//
#include <cassert>
#include <iostream>
#include <memory>
#include "../../domain/GenericProduct.h"
#include "../../domain/ProductValidators.h"
#include "../../repository/RepositoryException.h"
#include "../../repository/InMemoryRepository.h"
#include "InMemoryRepositoryTests.h"


void testRepositoryAddAndFind() {
    auto validator = std::make_shared<domain::GenericProductValidator>();
    repository::InMemoryRepository repo(validator);

    auto product = std::make_shared<domain::GenericProduct>("A1", "Cola", 150);
    repo.add(product);

    auto found = repo.findById("A1");
    assert(found != nullptr);
    assert(found->getId() == "A1");
    assert(found->getName() == "Cola");
    assert(found->getPrice() == 150);
}

void testRepositoryAddDuplicate() {
    auto validator = std::make_shared<domain::GenericProductValidator>();
    repository::InMemoryRepository repo(validator);

    auto product1 = std::make_shared<domain::GenericProduct>("B2", "Water", 100);
    auto product2 = std::make_shared<domain::GenericProduct>("B2", "Water 2", 120);
    repo.add(product1);

    try {
        repo.add(product2);
        assert(false); // should not reach this
    } catch (const repository::ProductAlreadyExistsException&) {
        assert(true); // expected
    }
}

void testRepositoryRemove() {
    auto validator = std::make_shared<domain::GenericProductValidator>();
    repository::InMemoryRepository repo(validator);

    auto product = std::make_shared<domain::GenericProduct>("C3", "Juice", 200);
    repo.add(product);

    repo.remove("C3");
    assert(repo.findById("C3") == nullptr);
}

void testRepositoryRemoveNonexistent() {
    auto validator = std::make_shared<domain::GenericProductValidator>();
    repository::InMemoryRepository repo(validator);

    try {
        repo.remove("Z9");
        assert(false); // should not reach this
    } catch (const repository::ProductNotFoundException&) {
        assert(true); // expected
    }
}

void testRepositoryUpdate() {
    auto validator = std::make_shared<domain::GenericProductValidator>();
    repository::InMemoryRepository repo(validator);

    auto product = std::make_shared<domain::GenericProduct>("D4", "Chips", 180);
    repo.add(product);

    auto updated = std::make_shared<domain::GenericProduct>("D4", "Chips Max", 200);
    repo.update("D4", updated);

    auto found = repo.findById("D4");
    assert(found->getName() == "Chips Max");
    assert(found->getPrice() == 200);
}

void testRepositoryUpdateNonexistent() {
    auto validator = std::make_shared<domain::GenericProductValidator>();
    repository::InMemoryRepository repo(validator);

    auto product = std::make_shared<domain::GenericProduct>("E5", "Tea", 120);
    try {
        repo.update("E5", product);
        assert(false); // should not reach this
    } catch (const repository::ProductNotFoundException&) {
        assert(true);
    }
}

void testRepositoryGetAll() {
    auto validator = std::make_shared<domain::GenericProductValidator>();
    repository::InMemoryRepository repo(validator);

    repo.add(std::make_shared<domain::GenericProduct>("F6", "Water", 100));
    repo.add(std::make_shared<domain::GenericProduct>("G7", "Soda", 150));

    auto all = repo.getAll();
    assert(all.size() == 2);
    assert((all[0]->getId() == "F6" || all[0]->getId() == "G7"));
    assert((all[1]->getId() == "F6" || all[1]->getId() == "G7"));
}

void testAllRepositoryTests() {
    testRepositoryAddAndFind();
    testRepositoryAddDuplicate();
    testRepositoryRemove();
    testRepositoryRemoveNonexistent();
    testRepositoryUpdate();
    testRepositoryUpdateNonexistent();
    testRepositoryGetAll();
}
