#pragma once

#include "./ship.hpp"
#include "vector_2.hpp"
class Kreuzer : public Ship {
public:
  Kreuzer(Vector2);
  ~Kreuzer() override;

  void attack(Ship *) override;
  void take_damage(int) override;
};
