#include "dish.h"

Dish::Dish(const std::string& name, const std::vector<Ingredient>& ingredients)
    : name(name), ingredients(ingredients) {}

std::string Dish::getName() const { return name; }
std::vector<Ingredient> Dish::getIngredients() const { return ingredients; }

void Dish::setName(const std::string& name) { this->name = name; }
void Dish::setIngredients(const std::vector<Ingredient>& ingredients) { this->ingredients = ingredients; }
