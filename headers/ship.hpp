#pragma once

#include "vector_2.hpp"
class Ship {
protected:
  int health;
  int size;
  int damage;
  double attack_distance;
  Vector2 position;

  Ship() = default;
  Ship(int h, int s, int d, double ad, Vector2 v)
      : health(h), size(s), damage(d), attack_distance(ad), position(v) {}

public:
  virtual ~Ship() = default;

  int get_health() const;
  int get_size() const;
  int get_damage() const;
  double get_attack_distance() const;
  const Vector2 &get_position() const;

  void move_closer_to_other_ship(const Vector2 &);

  virtual void attack(Ship *) = 0;
  virtual void take_damage(int) = 0;
};
