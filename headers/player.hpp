#pragma once

#include "./ship.hpp"
#include <vector>
class Player {
private:
  std::vector<Ship *> ships;

public:
  Player(std::vector<Ship *>);
  ~Player();

  Ship *get_random_ship();
  void check_ships();
  int get_ship_count();

  const std::vector<Ship *> &get_ships() const;
};
