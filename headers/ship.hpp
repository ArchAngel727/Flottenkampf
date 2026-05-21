#pragma once

class Ship {
protected:
  int health;
  int size;
  int damage;

  Ship() = default;
  Ship(int h, int s, int d) : health(h), size(s), damage(d) {}

public:
  virtual ~Ship() = default;

  int get_health() const;
  int get_size() const;
  int get_damage() const;

  virtual void attack(Ship *) = 0;
  virtual void take_damage(int) = 0;
  virtual void special(Ship *) = 0;
};
