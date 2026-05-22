#pragma once

#include "vector_2.hpp"
class Ship {
protected:
  int health;
  int size;
  int damage;
  Vector2 position;

  Ship() = default;
  Ship(int h, int s, int d, Vector2 v)
      : health(h), size(s), damage(d), position(v) {}

public:
  virtual ~Ship() = default;

  int get_health() const;
  int get_size() const;
  int get_damage() const;
  const Vector2 &get_position() const;

  virtual void attack(Ship *) = 0;
  virtual void take_damage(int) = 0;
};
