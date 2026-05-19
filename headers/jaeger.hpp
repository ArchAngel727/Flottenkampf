#pragma once

#include "./ship.hpp"
class Jaeger : public Ship {
private:
  int health;
  int size;
  int damage;

public:
  Jaeger();
  ~Jaeger() override;

  void attack(Ship *) override;
  void take_damage(int) override;
  void special(Ship *) override;
};
