#include "../headers/player.hpp"
#include <algorithm>
#include <cstdlib>
#include <vector>

Player::Player(std::vector<Ship *> ships) : ships(ships) {}

Player::~Player() {
  for (auto ship : this->ships) {
    delete ship;
  }
}

Ship *Player::get_random_ship() {
  if (this->ships.empty()) {
    return nullptr;
  }

  return this->ships[rand() % this->ships.size()];
}

void Player::check_ships() {
  auto new_end =
      std::remove_if(this->ships.begin(), this->ships.end(), [](Ship *s) {
        if (s == nullptr || s->get_health() <= 0) {
          delete s;
          return true;
        }
        return false;
      });
  ships.erase(new_end, ships.end());
}

int Player::get_ship_count() { return this->ships.size(); }

const std::vector<Ship *> &Player::get_ships() const { return this->ships; }
