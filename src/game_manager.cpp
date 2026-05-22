#include "../headers/game_manager.hpp"
#include "../headers/jaeger.hpp"
#include "../headers/kreuzer.hpp"
#include "../headers/zerstoerer.hpp"
#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

enum ShipType {
  Jaeger = 0,
  Zerstoere = 1,
  Kreuzer = 2,
};

void init_ship(std::vector<Ship *> &vec, std::vector<Ship *> &all_ships,
               ShipType type) {
  bool not_done = true;
  int num = 0;
  std::string str;

  while (not_done) {
    std::cout << "Enter number [0..=9] of ";

    switch (type) {
    case ShipType::Jaeger:
      std::cout << "Jäger";
      break;
    case Zerstoere:
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
      bool selecting_pos = true;
      Vector2 pos;

      while (selecting_pos) {
        pos.set_x(rand() % 11);
        pos.set_y(rand() % 11);

        for (auto ship : all_ships) {
          if (ship == nullptr) {
            continue;
          }

          if (pos == ship->get_position()) {
            continue;
          }
        }

        selecting_pos = false;
      }

      switch (type) {
      case ShipType::Jaeger:
        vec.push_back(new class Jaeger(pos));
        break;
      case Zerstoere:
        vec.push_back(new class Zerstoerer(pos));
        break;
      case Kreuzer:
        vec.push_back(new class Kreuzer(pos));
        break;
      }

      num -= 1;
    }

    not_done = false;
  }
}

GameManager::GameManager() {
  this->turn = 0;

  while (this->players.size() < 2) {
    std::vector<Ship *> ships;
    std::vector<Ship *> all_ships;

    for (auto player : this->players) {
      for (auto ship_ptr : player->get_ships()) {
        all_ships.push_back(ship_ptr);
      }
    }

    init_ship(ships, all_ships, ShipType::Jaeger);
    init_ship(ships, all_ships, ShipType::Zerstoere);
    init_ship(ships, all_ships, ShipType::Kreuzer);

    Player *player = new Player(ships);

    this->players.push_back(player);
  }
}

GameManager::~GameManager() {}

void play_turn(Player &current, Player &other) {
  Ship *attack_ship = current.get_random_ship();
  Ship *attacked_ship = other.get_random_ship();

  if (attack_ship == nullptr || attacked_ship == nullptr) {
    return;
  }

  const int *x_1 = &attack_ship->get_position().get_x();
  const int *x_2 = &attacked_ship->get_position().get_x();
  const int *y_1 = &attack_ship->get_position().get_y();
  const int *y_2 = &attacked_ship->get_position().get_y();

  // std::cout << "\nx_1: " << *x_1 << " x_2: " << *x_2 << '\n';
  // std::cout << "\ny_1: " << *y_1 << " y_2: " << *y_2 << '\n';

  double x = std::max(*x_1, *x_2) - std::min(*x_1, *x_2);
  double y = std::max(*y_1, *y_2) - std::min(*y_1, *y_2);

  // std::cout << "\nx: " << x << " y: " << y << '\n';

  double distance = std::sqrt(x * x + y * y);

  // TODO: store ship type and read it to determine attacking distance
  attacked_ship->take_damage(attack_ship->get_damage());

  std::cout << "Ship1: ";
  std::cout << attack_ship->get_position() << ' ';
  std::cout << '<' << attack_ship->get_health() << ", ";
  std::cout << attack_ship->get_damage() << '>' << ' ';

  // std::cout << "\ndist" << distance << '\n';

  std::cout << "Ship2: ";
  std::cout << attack_ship->get_position() << ' ';
  std::cout << '<' << attacked_ship->get_health() << ", ";
  std::cout << attacked_ship->get_damage() << '>' << '\n';
}

void GameManager::loop() {
  this->running = true;

  while (1) {
    for (auto player : this->players) {
      player->check_ships();

      if (player->get_ship_count() == 0) {
        this->running = false;
      }
    }

    if (!this->running) {
      break;
    }

    if (this->turn == 0) {
      play_turn(*this->players[0], *this->players[1]);
    } else {
      play_turn(*this->players[1], *this->players[0]);
    }

    this->turn = (this->turn + 1) % 2;
  }
}
