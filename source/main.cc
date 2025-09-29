#include <raylib.h>

#include <print>

#include "../extern/raygui.h"
#include "../header/game.hpp"

// TODO(2025-09-24 17:11:03): make a map model in blender
// TODO(2025-09-24 17:11:03): put that map in the game and collisions...

int main() {
  InitWindow(1200, 1000, "nowrd");
  SetWindowState(FLAG_WINDOW_RESIZABLE);  // | FLAG_BORDERLESS_WINDOWED_MODE);
  SetExitKey({});
  Game g = game::init_game("Kate");
  // Start with cursor enabled since we begin in menu mode
  EnableCursor();
  std::println("hewwo {}, UwU", g.playerName);

  while (!WindowShouldClose() && !g.shouldExit) {
    float dt = GetFrameTime();
    game::update(g, dt);
    game::draw(g);


    player::debug(g.player);
    cam::debug(g.player.cam);
  }
  EnableCursor();

  return 0;
}
