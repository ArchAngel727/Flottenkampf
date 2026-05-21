#include "../headers/player.hpp"
#include "../headers/jaeger.hpp"
#include "../headers/kreuzer.hpp"
#include "../headers/zerstoerer.hpp"
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

enum ShipType {
  Jaeger = 0,
  Zersoerer = 1,
  Kreuzer = 2,
};

void init_ship(std::vector<Ship *> &vec, ShipType type) {
  bool not_done = true;
  int num = 0;
  std::string str;

  while (not_done) {
    std::cout << "Enter number [0..=9] of ";

    switch (type) {
    case ShipType::Jaeger:
      std::cout << "Jäger";
      break;
    case Zersoerer:
      std::cout << "Zerstörer";
      break;
    case Kreuzer:
      std::cout << "Kreuzer";
      break;
    }

    std::cout << ": ";

    std::cin >> str;

    try {
      num = std::stoi(str);
    } catch (std::exception) {
      continue;
    }

    if (num <= 0 || num > 9) {
      continue;
    }

    while (num > 0) {
      switch (type) {
      case ShipType::Jaeger:
        vec.push_back(new class Jaeger());
        break;
      case Zersoerer:
        vec.push_back(new class Zerstoerer());
        break;
      case Kreuzer:
        vec.push_back(new class Kreuzer());
        break;
      }

      num -= 1;
    }

    not_done = false;
  }
}

Player::Player() {
  init_ship(this->ships, ShipType::Jaeger);
  init_ship(this->ships, ShipType::Zersoerer);
  init_ship(this->ships, ShipType::Kreuzer);
}

Player::~Player() {
  for (auto ship : this->ships) {
    delete ship;
    std::cout << ship->get_health();
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
