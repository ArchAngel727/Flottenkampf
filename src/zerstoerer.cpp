#include "../headers/zerstoerer.hpp"
#include <cstdlib>

Zerstoerer::Zerstoerer() : Ship(150, 6, 60) {}

Zerstoerer::~Zerstoerer() {}

void Zerstoerer::attack(Ship *other) {
  if ((rand() % 11) - 2 >= other->get_size()) {
    other->take_damage(this->get_damage());
  }
}

void Zerstoerer::take_damage(int damage) { this->health -= damage; }
void Zerstoerer::special(Ship *other) {}
