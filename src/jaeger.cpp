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

    if (this->level >= 1 && rand() % 2 == 0) {
      this->move_closer_to(other->get_position());
    }
  }
}

void Jaeger::take_damage(int damage) {
  int roll = rand() % 10;

  if (this->level >= 1 && roll == 0) {
    return;
  }

  this->health -= damage;
}

void Jaeger::level_up() {
  this->xp = 0;
  this->level += 1;
}
