#include "../headers/jaeger.hpp"
#include <cstdlib>

Jaeger::Jaeger() : health(75), size(4), damage(30) {}

Jaeger::~Jaeger() {}

void Jaeger::attack(Ship *other) {
  if (rand() % 11 >= other->get_size()) {
    other->take_damage(this->get_damage());
  }
}

void Jaeger::take_damage(int damage) { this->health -= damage; }
void Jaeger::special(Ship *other) {}
