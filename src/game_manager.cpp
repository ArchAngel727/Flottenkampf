#include "../headers/game_manager.hpp"
#include <iostream>
#include <vector>

GameManager::GameManager() {
  this->turn = 0;

  this->players.push_back(new Player());
  this->players.push_back(new Player());
}

GameManager::~GameManager() {}

void play_turn(Player &current, Player &other) {
  Ship *attack_ship = current.get_random_ship();
  Ship *attacked_ship = other.get_random_ship();

  if (attack_ship == nullptr || attacked_ship == nullptr) {
    return;
  }

  attacked_ship->take_damage(attack_ship->get_damage());

  std::cout << '<' << attack_ship->get_health() << ", ";
  std::cout << attack_ship->get_damage() << '>' << ' ';

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
