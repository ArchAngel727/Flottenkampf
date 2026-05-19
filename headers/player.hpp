#pragma once

#include "./ship.hpp"
#include <vector>
class Player {
private:
  std::vector<Ship *> ships;

public:
  Player();
  ~Player();
};
