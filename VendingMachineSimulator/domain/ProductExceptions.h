
#ifndef VALIDATORS_H
#define VALIDATORS_H
#include <stdexcept>
#include <iostream>
#include <utility>

namespace domain {
    class VendingMachineExcpetion : public std::exception {
    private:
        std::string message;
    public:
        explicit VendingMachineExcpetion(std::string message) : message(std::move(message)) {};
        ~VendingMachineExcpetion() override = default;
        [[nodiscard]] const char* what() const noexcept override {return message.c_str();};
    };

    class ProductException : public std::exception {
    private:
        std::string message;
    public:
        explicit ProductException(std::string message) : message(std::move(message)) {};
        ~ProductException() override = default;
        [[nodiscard]] const char* what() const noexcept override {return message.c_str();};
    };

    class ProductValidationException : public ProductException {
    private:
        std::string message;
    public:
        explicit ProductValidationException(std::string message) : ProductException(std::move(message)) {};
        ~ProductValidationException() override = default;
        [[nodiscard]] const char* what() const noexcept override {return message.c_str();};

    };
}

// class ProductNotFoundException : public ProductException {
// private:
//     std::string message;
// public:
//     explicit ProductNotFoundException(std::string message) : ProductException(std::move(message)) {};
//     ~ProductNotFoundException() override = default;
//     [[nodiscard]] const char* what() const noexcept override {return message.c_str();};
// };
//
// class ProductAlreadyExistsException : public ProductException {
// private:
//     std::string message;
// public:
//     explicit ProductAlreadyExistsException(std::string message) : ProductException(std::move(message)) {};
//     ~ProductAlreadyExistsException() override = default;
//     [[nodiscard]] const char* what() const noexcept override {return message.c_str();};
// };


#endif //VALIDATORS_H
