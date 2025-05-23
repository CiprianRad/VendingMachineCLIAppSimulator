//
// Created by cipri on 5/17/2025.
//

#ifndef PRODUCTVALIDATORS_H
#define PRODUCTVALIDATORS_H
#include "Product.h"
#include "GenericProduct.h"
#include <string>

#include "ProductExceptions.h"
#include "ProductValidators.h"

namespace domain {
    class ProductValidator {
    public:
        virtual ~ProductValidator() = default;
        virtual void validate(const Product &product) const = 0;
    };

    class GenericProductValidator : public ProductValidator {
    public:
        void validate(const Product &product) const override {
            const auto* genericProduct = dynamic_cast<const GenericProduct*>(&product);
            if (genericProduct == nullptr) {
                throw ProductValidationException("Product object expected");
            }
            if (genericProduct->getName().empty()) {
                throw ProductValidationException("Product name cannot be empty");
            }
            if (genericProduct->getPrice() < 0) {
                throw ProductValidationException("Product price cannot be negative");
            }
            if (genericProduct->getId().empty()) {
                throw ProductValidationException("Product id cannot be empty");
            }

        }
    };
}

#endif //PRODUCTVALIDATORS_H
