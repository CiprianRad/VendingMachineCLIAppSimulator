//
// Created by cipri on 5/17/2025.
//

#ifndef FILEREPOSITORY_H
#define FILEREPOSITORY_H
#include "InMemoryRepository.h"
#include "../domain/Product.h"
#include "FileRepositoryException.h"
#include <filesystem>
#include <fstream>

namespace repository {
    // class FileRepository : public InMemoryRepository {
    // private:
    //     std::string fileName;
    //     std::shared_ptr<domain::ProductValidator> validator;
    //     bool isLoading = false;
    //     void loadData();
    //     void saveData();
    //
    // public:
    //     explicit FileRepository(std::string fileName, std::shared_ptr<domain::ProductValidator> validator) : fileName(fileName), InMemoryRepository(validator) {loadData();}
    //     void add(std::shared_ptr<domain::Product> product) override;
    //     void update(const std::string &key, std::shared_ptr<domain::Product> product) override;
    //     void remove(const std::string &key) override;
    //     [[nodiscard]] std::vector<std::shared_ptr<domain::Product>> getAll() const override;
    //     std::shared_ptr<domain::Product> findById(const std::string &key) const override;
    // };

    class FileRepository : public InMemoryRepository {
    private:
        std::string fileName;
        std::shared_ptr<domain::ProductValidator> validator;
        bool isLoading = false;  // prevents recursive save during load

    public:
        explicit FileRepository(const std::string& fileName, std::shared_ptr<domain::ProductValidator> validator);

        void loadData();
        void saveData();

        // std::unordered_map<std::string, int> loadProductQuantities();

        void add(std::shared_ptr<domain::Product> product) override;
        void remove(const std::string& key) override;
        void update(const std::string& key, std::shared_ptr<domain::Product> product) override;

        std::vector<std::shared_ptr<domain::Product>> getAll() const override;
        std::shared_ptr<domain::Product> findById(const std::string& key) const override;
    };
}

#endif //FILEREPOSITORY_H
