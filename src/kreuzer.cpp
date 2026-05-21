#include "../headers/kreuzer.hpp"
#include <cstdlib>

Kreuzer::Kreuzer() : Ship(250, 8, 50) {}

Kreuzer::~Kreuzer() {}

void Kreuzer::attack(Ship *other) {
  if (rand() % 11 >= other->get_size()) {
    other->take_damage(this->get_damage());
    this->attack(other);
  }
}

void Kreuzer::take_damage(int damage) { this->health -= damage; }
void Kreuzer::special(Ship *other) {}
