#include "../headers/zerstoerer.hpp"
#include <cstdlib>

Zerstoerer::Zerstoerer(Vector2 pos) : Ship(150, 6, 60, 4, pos) {}

Zerstoerer::~Zerstoerer() {}

void Zerstoerer::attack(Ship *other, int extra) {
  this->xp += 1;

  if ((rand() % 11) - 2 >= other->get_size()) {
    other->take_damage(this->get_damage() + extra);

    if (this->level >= 1) {
      other->take_damage(this->get_damage() + extra);
    }
  }
}

void Zerstoerer::take_damage(int damage) {
  int roll = rand() % 10;

  if (this->level >= 1 && roll == 0) {
    return;
  }

  this->health -= damage;
}

void Zerstoerer::level_up() {
  this->xp = 0;
  this->level += 1;
}
