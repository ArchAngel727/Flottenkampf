#include "../headers/game_manager.hpp"
#include "../headers/jaeger.hpp"
#include "../headers/kreuzer.hpp"
#include "../headers/log.hpp"
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

GameManager::GameManager() : turn(0), renderer(10, 10, 2) {
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

  crazylogger::log("x_1: {}, x_2: {}", *x_1, *x_2);
  crazylogger::log("y_1: {}, y_2: {}", *y_1, *y_2);

  double x = std::max(*x_1, *x_2) - std::min(*x_1, *x_2);
  double y = std::max(*y_1, *y_2) - std::min(*y_1, *y_2);

  crazylogger::log("x: {}, y: {}", x, y);

  double distance = std::sqrt(x * x + y * y);

  if (attack_ship->get_attack_distance() > distance) {
    attacked_ship->take_damage(attack_ship->get_damage());
  } else {
    crazylogger::log("Performing crazy manover to move closer to enemy ship "
                     "(crazy shit indeed)\n");
    attack_ship->move_closer_to_other_ship(attacked_ship->get_position());
  }

  crazylogger::log("Ship1; pos: {}, hp: {}>",
                   attack_ship->get_position().to_string(),
                   attack_ship->get_damage());
  crazylogger::log("Ship2; pos: {}, hp: {}>",
                   attacked_ship->get_position().to_string(),
                   attacked_ship->get_damage());
  crazylogger::log("dist: {}", distance);
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

    // if (this->turn == 0) {
    //   play_turn(*this->players[0], *this->players[1]);
    // } else {
    //   play_turn(*this->players[1], *this->players[0]);
    // }

    this->turn = (this->turn + 1) % 2;

    this->renderer.render_to_buffer();
    this->renderer.print();

    break;
  }
}
