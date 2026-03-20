//
// Created by cipri on 5/18/2025.
//

#ifndef VMCONTROLLEREXCEPTIONS_H
#define VMCONTROLLEREXCEPTIONS_H

#include <exception>
#include <string>
#include <utility>

namespace controller {

    class VendingMachineException : public std::exception {
    protected:
        std::string message;
    public:
        explicit VendingMachineException(std::string message)
            : message(std::move(message)) {}
        ~VendingMachineException() override = default;

        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }
    };

    class FileOpenException : public VendingMachineException {
    public:
        explicit FileOpenException(const std::string& fileName)
            : VendingMachineException("Failed to open file: " + fileName) {}
    };

    class InvalidBanknoteFormatException : public VendingMachineException {
    public:
        InvalidBanknoteFormatException()
            : VendingMachineException("Invalid line in banknotes file: value must be > 0 and quantity >= 0") {}
    };

    class OutOfStockException : public VendingMachineException {
    public:
        explicit OutOfStockException(const std::string& productId)
            : VendingMachineException("Product '" + productId + "' is out of stock.") {}
    };

    class ProductUnavailableException : public VendingMachineException {
    public:
        explicit ProductUnavailableException(const std::string& productId)
            : VendingMachineException("Product '" + productId + "' no longer available in repository.") {}
    };

    class InsufficientPaymentException : public VendingMachineException {
    public:
        InsufficientPaymentException(int required, int paid)
            : VendingMachineException("Insufficient payment. Required: " + std::to_string(required) + ", Paid: " + std::to_string(paid)) {}
    };

    class ChangeUnavailableException : public VendingMachineException {
    public:
        ChangeUnavailableException()
            : VendingMachineException("Cannot provide change with current banknotes.") {}
    };

    class NotEnoughBanknotesException : public VendingMachineException {
    public:
        explicit NotEnoughBanknotesException(int denom)
            : VendingMachineException("Not enough banknotes of denomination: " + std::to_string(denom)) {}
    };

    class InvalidQuantityException : public VendingMachineException {
    public:
        InvalidQuantityException()
            : VendingMachineException("Quantity must be positive.") {}
    };

    class NegativeQuantitySetException : public VendingMachineException {
    public:
        NegativeQuantitySetException()
            : VendingMachineException("Quantity must be non-negative.") {}
    };

}

#endif //VMCONTROLLEREXCEPTIONS_H
