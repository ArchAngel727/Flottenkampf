#include "../headers/kreuzer.hpp"
#include <cstdlib>

Kreuzer::Kreuzer(Vector2 pos) : Ship(250, 8, 50, 3, pos) {}

Kreuzer::~Kreuzer() {}

void Kreuzer::attack(Ship *other, int extra) {
  this->xp += 1;

  if (this->level >= 1 && rand() % 10 == 0) {
    this->health += 1;
  }

  if (rand() % 11 >= other->get_size()) {
    other->take_damage(this->get_damage() - extra);
    this->attack(other, extra);
  }
}

void Kreuzer::take_damage(int damage) {
  int roll = rand() % 10;

  if (this->level >= 1 && roll == 0) {
    return;
  }

  this->health -= damage;
}

void Kreuzer::level_up() {
  this->xp = 0;
  this->level += 1;
}
