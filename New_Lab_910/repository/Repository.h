//
// Created by cipri on 5/16/2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <string>
#include <vector>

// template <typename T>
// class Repository {
// public:
//     virtual ~Repository() = default;
//     virtual void add(T& element) = 0;
//     virtual void remove(const std::string &key) = 0;
//     virtual void update(const std::string &key, T& element) = 0;
//     virtual std::vector<T*> getAll() = 0;
//
// };
namespace repository {
    template <typename T>
    class Repository {
    public:
        virtual ~Repository() = default;

        virtual void add(std::shared_ptr<T> element) = 0;
        virtual void remove(const std::string& key) = 0;
        virtual void update(const std::string& key, std::shared_ptr<T> element) = 0;
        virtual std::vector<std::shared_ptr<T>> getAll() const = 0;
        virtual std::shared_ptr<T> findById(const std::string& key) const = 0;
    };
}
#endif //REPOSITORY_H
