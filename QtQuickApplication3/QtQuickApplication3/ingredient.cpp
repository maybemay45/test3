#include "ingredient.h"

Ingredient::Ingredient()
{
    //default constructor
}

Ingredient::Ingredient(const std::string& name, int quantity)
    : name(name), quantity(quantity) {}

std::string Ingredient::getName() const { return name; }
int Ingredient::getQuantity() const { return quantity; }

void Ingredient::setName(const std::string& name) { this->name = name; }
void Ingredient::setQuantity(int quantity) { this->quantity = quantity; }
