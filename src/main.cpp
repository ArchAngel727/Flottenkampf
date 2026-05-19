#include "../headers/game_manager.hpp"
#include <cstdlib>
#include <ctime>

int main() {
  std::srand(std::time(nullptr));
  GameManager gm;

  gm.loop();

  return 0;
}
