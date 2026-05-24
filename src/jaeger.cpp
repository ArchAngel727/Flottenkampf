#include "../headers/jaeger.hpp"
#include <cstdlib>

Jaeger::Jaeger(Vector2 pos) : Ship(75, 4, 30, 2, pos) {}

Jaeger::~Jaeger() {}

void Jaeger::attack(Ship *other, int extra) {
  int rand_num = rand() % 11;

  this->xp += 1;

  if (rand_num >= other->get_size()) {
    other->take_damage(this->get_damage() + extra);

    if (rand_num > 8) {
      other->take_damage(this->get_damage() + extra);
    }
  }
}

void Jaeger::take_damage(int damage) { this->health -= damage; }
void Jaeger::level_up() { this->xp = 0; }
