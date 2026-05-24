#pragma once

#include "vector_2.hpp"
class Ship {
protected:
  int health;
  int size;
  int damage;
  int xp = 0;
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
  int get_xp() const;
  double get_attack_distance() const;
  const Vector2 &get_position() const;

  double distance_to(Ship *) const;

  void move_closer_to(const Vector2 &);

  virtual void attack(Ship *, int = 0) = 0;
  virtual void take_damage(int) = 0;
  virtual void level_up() = 0;
};
