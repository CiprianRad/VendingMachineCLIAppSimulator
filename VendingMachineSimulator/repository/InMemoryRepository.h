

#ifndef INMEMORYREPOSITORY_H
#define INMEMORYREPOSITORY_H
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include "../domain/Product.h"
#include "Repository.h"
#include "../domain/ProductValidators.h"
#include "RepositoryException.h"

namespace repository {
    class InMemoryRepository : public Repository<domain::Product> {
    private:
        std::unordered_map<std::string, std::shared_ptr<domain::Product>> products;
        std::shared_ptr<domain::ProductValidator> validator;

    public:

        explicit InMemoryRepository(std::shared_ptr<domain::ProductValidator> validator): validator(std::move(validator)) {};
        ~InMemoryRepository() override = default;

        void add(std::shared_ptr<domain::Product> element) override;
        void remove(const std::string& key) override;
        void update(const std::string& key, std::shared_ptr<domain::Product> element) override;
        std::vector<std::shared_ptr<domain::Product>> getAll() const override;
        std::shared_ptr<domain::Product> findById(const std::string& key) const override;
    };
}
#endif //INMEMORYREPOSITORY_H
