//
// Created by cipri on 5/17/2025.
//

#ifndef FILEREPOSITORYEXCEPTION_H
#define FILEREPOSITORYEXCEPTION_H
#include <exception>

#include "../domain/ProductExceptions.h"

namespace repository {
    class FileRepositoryException : public domain::ProductException {
    private:
        std::string message;
    public:
        explicit FileRepositoryException(std::string message) : ProductException(std::move(message)) {}
        ~FileRepositoryException() override = default;
        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }
    };

    class InvalidLineFormatException : public FileRepositoryException {
    private:
        std::string message;
    public:
        InvalidLineFormatException(std::string message) : FileRepositoryException(std::move(message)) {}
        ~InvalidLineFormatException() override = default;
        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }
    };
}

#endif //FILEREPOSITORYEXCEPTION_H
