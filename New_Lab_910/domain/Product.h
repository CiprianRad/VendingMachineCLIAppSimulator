//
// Created by cipri on 5/16/2025.
//

#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
namespace domain {
    class Product {
    public:
        virtual ~Product() = default;

        [[nodiscard]] virtual std::string getId() const = 0;
        [[nodiscard]] virtual std::string getName() const = 0;
        [[nodiscard]] virtual int getPrice() const = 0;

        virtual void setPrice(const int &value) = 0;
        virtual void setName(const std::string& name) = 0;
    };
}


#endif //PRODUCT_H
