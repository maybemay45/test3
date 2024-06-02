#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
public:
    Ingredient();
    Ingredient(const std::string& name, int quantity);

    std::string getName() const;
    int getQuantity() const;

    void setName(const std::string& name);
    void setQuantity(int quantity);

private:
    std::string name;
    int quantity;
};

#endif // INGREDIENT_H
#pragma once
