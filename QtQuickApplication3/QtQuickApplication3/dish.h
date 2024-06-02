#ifndef DISH_H
#define DISH_H

#include <string>
#include <vector>
#include "ingredient.h"

class Dish {
public:
    Dish(const std::string& name, const std::vector<Ingredient>& ingredients);

    std::string getName() const;
    std::vector<Ingredient> getIngredients() const;

    void setName(const std::string& name);
    void setIngredients(const std::vector<Ingredient>& ingredients);

private:
    std::string name;
    std::vector<Ingredient> ingredients;
};

#endif // DISH_H
#pragma once
