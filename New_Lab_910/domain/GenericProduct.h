//
// Created by cipri on 5/16/2025.
//

#ifndef GENERICPRODUCT_H
#define GENERICPRODUCT_H
#include "Product.h"
#include <iostream>

namespace domain {
    class GenericProduct : public Product {
    private:
        std::string id;
        std::string name;
        int price;
    public:
        GenericProduct();
        explicit GenericProduct(const std::string &id, const std::string &name, int price);
        ~GenericProduct() override = default;
        [[nodiscard]] std::string getId() const override;
        [[nodiscard]] std::string getName() const override;
        [[nodiscard]] int getPrice() const override;
        void setPrice(const int &value) override;
        void setName(const std::string &value) override;

        friend std::ostream& operator<<(std::ostream& os, const GenericProduct& product);
        friend std::istream& operator>>(std::istream& is, GenericProduct& product);

    };
}

#endif //GENERICPRODUCT_H
