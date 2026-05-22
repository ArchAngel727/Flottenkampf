#pragma once

#include "./ship.hpp"
#include "vector_2.hpp"
class Jaeger : public Ship {
public:
  Jaeger(Vector2);
  ~Jaeger() override;

  void attack(Ship *) override;
  void take_damage(int) override;
};
