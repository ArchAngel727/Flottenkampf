#pragma once

#include "./ship.hpp"
class Zerstoerer : public Ship {
public:
  Zerstoerer();
  ~Zerstoerer() override;

  void attack(Ship *) override;
  void take_damage(int) override;
  void special(Ship *) override;
};
