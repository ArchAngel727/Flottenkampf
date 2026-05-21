#pragma once

#include "./ship.hpp"
class Kreuzer : public Ship {
public:
  Kreuzer();
  ~Kreuzer() override;

  void attack(Ship *) override;
  void take_damage(int) override;
  void special(Ship *) override;
};
