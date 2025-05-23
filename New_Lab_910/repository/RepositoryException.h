//
// Created by cipri on 5/17/2025.
//

#ifndef REPOSITORYEXCEPTION_H
#define REPOSITORYEXCEPTION_H
#include "../domain/ProductExceptions.h"

namespace repository {
    class ProductNotFoundException : public domain::ProductException {
    private:
        std::string message;
    public:
        explicit ProductNotFoundException(std::string message) : ProductException(std::move(message)) {};
        ~ProductNotFoundException() override = default;
        [[nodiscard]] const char* what() const noexcept override {return message.c_str();};
    };

    class ProductAlreadyExistsException : public domain::ProductException {
    private:
        std::string message;
    public:
        explicit ProductAlreadyExistsException(std::string message) : ProductException(std::move(message)) {};
        ~ProductAlreadyExistsException() override = default;
        [[nodiscard]] const char* what() const noexcept override {return message.c_str();};
    };
}


#endif //REPOSITORYEXCEPTION_H
