#include "../headers/player.hpp"
#include "../headers/jaeger.hpp"
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
    case Zersoerer:
    case Kreuzer:
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
      case Kreuzer:
        break;
      }

      num -= 1;
    }

    not_done = false;
  }
}

Player::Player() { init_ship(this->ships, ShipType::Jaeger); }

Player::~Player() {
  for (auto ship : this->ships) {
    delete ship;
  }
}
