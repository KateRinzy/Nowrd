#include "../header/game.hpp"

#include <raylib.h>

#include <string>

#include "../header/ui.hpp"

namespace game {
Game init_game(std::string playerName) {
  struct Player p = player::init_player();
  struct World w = world::init();
  return {p, w, playerName, true, false, ui::init()};
}

void update(Game &g, float deltaTime) {
  ui::update(g);
  if (!g.isInMenu) {
    player::update(g.player, g.world, deltaTime);
    player::updateCamera(g.player, deltaTime);
  }
}

void draw(Game &g) {
  BeginDrawing();
  if (g.isInMenu) {
    ClearBackground({40, 40, 40, 255});
    ui::draw(g);
  } else {
    ClearBackground({20, 20, 20, 255});
    BeginMode3D(g.player.cam.camera);
    player::draw(g.player);
    world::draw(g.world);

    DrawGrid(200, 1);
    EndMode3D();
  }
  EndDrawing();
}
}  // namespace game
