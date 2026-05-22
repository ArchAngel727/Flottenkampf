#pragma once

#include "./ship.hpp"
#include "vector_2.hpp"
class Zerstoerer : public Ship {
public:
  Zerstoerer(Vector2);
  ~Zerstoerer() override;

  void attack(Ship *) override;
  void take_damage(int) override;
};
