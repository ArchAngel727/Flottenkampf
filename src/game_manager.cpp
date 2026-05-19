#include "../headers/game_manager.hpp"
#include <iostream>
#include <string>
#include <vector>

GameManager::GameManager() {
  this->players.push_back(Player());
  this->players.push_back(Player());
}

GameManager::~GameManager() {}

std::vector<std::string> split(std::string s, const std::string &delimiter) {
  std::vector<std::string> tokens;
  size_t pos = 0;
  std::string token;

  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    tokens.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  tokens.push_back(s);

  return tokens;
}

bool run_command(std::string cmd) {
  auto cmds = split(cmd, " ");

  return false;
}

void GameManager::loop() {
  std::string cmd;
  this->running = true;

  while (this->running) {
    if (!std::getline(std::cin, cmd)) {
      break;
    }

    if (cmd.empty()) {
      continue;
    }

    if (run_command(cmd)) {
      this->running = false;
    }
  }
}
