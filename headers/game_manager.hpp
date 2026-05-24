#pragma once

#include "./player.hpp"
#include "renderer.hpp"
#include <vector>
class GameManager {
private:
  bool running;
  size_t turn;
  Renderer *renderer;
  std::vector<Player *> players;

public:
  GameManager();
  ~GameManager();

  void loop();
};
