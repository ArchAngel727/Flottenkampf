#pragma once

#include "./player.hpp"
#include <vector>
class GameManager {
private:
  std::vector<Player *> players;
  bool running;
  size_t turn;

public:
  GameManager();
  ~GameManager();

  void loop();
};
