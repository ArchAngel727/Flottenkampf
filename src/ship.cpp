#include "../headers/ship.hpp"
#include <algorithm>
#include <cmath>
#include <vector>

int Ship::get_health() const { return this->health; }
int Ship::get_size() const { return this->size; }
int Ship::get_damage() const { return this->damage; }
double Ship::get_attack_distance() const { return this->attack_distance; }
const Vector2 &Ship::get_position() const { return this->position; }

void Ship::move_closer_to_other_ship(const Vector2 &other_pos) {
  Vector2 vec[] = {
      Vector2(this->get_position()) + Vector2(1, 0),
      Vector2(this->get_position()) + Vector2(0, 1),
      Vector2(this->get_position()) + Vector2(-1, 0),
      Vector2(this->get_position()) + Vector2(0, -1),
  };

  const Vector2 *next_move = nullptr;
  double distances[] = {
      0.0,
      0.0,
      0.0,
      0.0,
  };

  for (int i = 0; i < 4; i++) {
    Vector2 *current_pos = &vec[i];
    double x = std::pow(current_pos->get_x() - other_pos.get_x(), 2);
    double y = std::pow(current_pos->get_y() - other_pos.get_y(), 2);

    distances[i] = std::sqrt(x + y);
  }

  for (auto &vector : vec) {
    if (other_pos == vector) {
      next_move = nullptr;
    }
  }

  if (next_move == nullptr) {
    next_move = &vec[std::distance(
        std::begin(distances),
        std::min_element(std::begin(distances), std::end(distances)))];
  }

  this->position = *next_move;

  if (this->position.get_x() < 0) {
    this->position.set_x(0);
  }

  if (this->position.get_y() < 0) {
    this->position.set_y(0);
  }

  if (this->position.get_x() > 4) {
    this->position.set_x(4);
  }

  if (this->position.get_y() > 4) {
    this->position.set_y(4);
  }
}
