#include "../headers/zerstoerer.hpp"
#include <cstdlib>

Zerstoerer::Zerstoerer(Vector2 pos) : Ship(150, 6, 60, 6, pos) {}

Zerstoerer::~Zerstoerer() {}

void Zerstoerer::attack(Ship *other) {
  if ((rand() % 11) - 2 >= other->get_size()) {
    other->take_damage(this->get_damage());
  }
}

void Zerstoerer::take_damage(int damage) { this->health -= damage; }
