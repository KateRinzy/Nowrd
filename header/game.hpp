#pragma once

#include <raylib.h>

#include <string>

#include "../header/player.hpp"
#include "../header/ui.hpp"
#include "../header/world.hpp"

struct Game {
  Player player;
  World world;
  std::string playerName;
  bool isInMenu;
  bool shouldExit;
  UI gui;
};

namespace game {
Game init_game(std::string playerName);
void update(Game &game, float deltaTime);
void draw(Game &game);
}  // namespace game