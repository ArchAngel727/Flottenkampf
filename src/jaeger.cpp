#include "../headers/jaeger.hpp"
#include <cstdlib>

Jaeger::Jaeger() : Ship(75, 4, 30) {}

Jaeger::~Jaeger() {}

void Jaeger::attack(Ship *other) {
  int rand_num = rand() % 11;

  if (rand_num >= other->get_size()) {
    other->take_damage(this->get_damage());

    if (rand_num > 8) {
      other->take_damage(this->get_damage());
    }
  }
}

void Jaeger::take_damage(int damage) { this->health -= damage; }
void Jaeger::special(Ship *other) {}
