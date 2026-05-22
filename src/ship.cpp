#include "../headers/ship.hpp"

int Ship::get_health() const { return this->health; }
int Ship::get_size() const { return this->size; }
int Ship::get_damage() const { return this->damage; }

const Vector2 &Ship::get_position() const { return this->position; }
