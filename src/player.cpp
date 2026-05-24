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
  for (Ship *&ship : this->ships) {
    if (ship == nullptr || ship->get_health() <= 0) {
      delete ship;
      ship = nullptr;
    }

    if (ship != nullptr) {
      if (ship->get_xp() > 5) {
        ship->level_up();
      }
    }
  }

  ships.erase(std::remove(this->ships.begin(), this->ships.end(), nullptr),
              this->ships.end());
}

int Player::get_ship_count() { return this->ships.size(); }

const std::vector<Ship *> &Player::get_ships() const { return this->ships; }
