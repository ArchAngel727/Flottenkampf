#include "../headers/game_manager.hpp"
#include "../headers/jaeger.hpp"
#include "../headers/kreuzer.hpp"
#include "../headers/zerstoerer.hpp"
#include <array>
#include <chrono>
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

enum ShipType {
  Jaeger = 0,
  Zerstoere = 1,
  Kreuzer = 2,
};

void clear() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

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
        pos.set_x(rand() % 10);
        pos.set_y(rand() % 10);

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

void play_turn(Player &current, Player &other) {
  Ship *attack_ship = current.get_random_ship();
  Ship *attacked_ship = other.get_random_ship();

  if (attack_ship == nullptr || attacked_ship == nullptr) {
    return;
  }

  double distance = attack_ship->distance_to(attacked_ship);

  if (attack_ship->get_attack_distance() > distance) {
    if (attack_ship->get_attack_distance() - 1 > distance) {
      attack_ship->attack(attacked_ship, -1);
    } else {
      attack_ship->attack(attacked_ship);
    }
  } else {
    attack_ship->move_closer_to(attacked_ship->get_position());
  }
}

GameManager::GameManager() : turn(0), renderer(new Renderer(10, 10, 2)) {
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

GameManager::~GameManager() {
  for (auto player : this->players) {
    delete player;
  }

  delete this->renderer;
}

void GameManager::loop() {
  this->running = true;
  std::array<const std::vector<Ship *> *, 2> ships = {
      &this->players[0]->get_ships(), &this->players[1]->get_ships()};

  while (1) {
    if (!this->running) {
      break;
    }

    if (this->turn % 2 == 0) {
      play_turn(*this->players[0], *this->players[1]);
    } else {
      play_turn(*this->players[1], *this->players[0]);
    }

    for (auto player : this->players) {
      player->check_ships();

      if (player->get_ship_count() == 0) {
        this->running = false;
      }
    }

    this->turn += 1;

    clear();

    std::cout << "Turn: " << this->turn << '\n';

    this->renderer->render_to_buffer(ships);
    this->renderer->print();
    this->renderer->clear_buffer();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}
