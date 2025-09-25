#include "../header/ui.hpp"

#include <raylib.h>

#include <print>

#include "../header/game.hpp"

bool isPointWithinRectangle(const Rectangle &rect, const Vector2 point) {
  return (point.x >= rect.x &&               //
          point.x <= rect.x + rect.width &&  //
          point.y >= rect.y &&               //
          point.y <= rect.y + rect.height    //
  );
};

namespace ui {
UI init() {
  UI currentUI = {};
  currentUI.elements.push_back({
      Rectangle{10, 10, 100, 32},  //
      "Exit",                      //
      [](Game &g) {
        g.shouldExit = true;
        return;
      },      //
      WHITE,  //
      RED     //
  });
  currentUI.elements.push_back({
      Rectangle{10, 50, 100, 32},  //
      "Start",                     //
      [](Game &g) {
        g.isInMenu = false;
        DisableCursor();
        return;
      },      //
      WHITE,  //
      GREEN   //
  });

  return currentUI;
};

void update(Game &g) {
  if (IsKeyPressed(KeyboardKey::KEY_ESCAPE)) {
    g.isInMenu = !g.isInMenu;
    // Immediately handle cursor state when menu state changes
    if (g.isInMenu) {
      EnableCursor();
    } else {
      DisableCursor();
    }
  }

  if (!g.isInMenu) return;

  Vector2 mousePosition = GetMousePosition();
  for (auto &e : g.gui.elements) {
    if (isPointWithinRectangle(e.button, mousePosition)) {
      // Check if mouse button is pressed while hovering
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        e.callback(g);
      }
      std::println("ui::update || hovering {}", e.name);
    }
  }
}

void draw(Game &g) {
  Vector2 mousePosition = GetMousePosition();
  std::println("ui::draw || mousePosition <{}, {}>", mousePosition.x, mousePosition.y);
  for (auto &e : g.gui.elements) {
    Color color = isPointWithinRectangle(e.button, mousePosition) ? e.hoveredColor : e.normalColor;
    DrawRectangle(e.button.x, e.button.y, e.button.width, e.button.height, color);
    DrawText(e.name.c_str(), e.button.x, e.button.y, 22, BLACK);

    if (CheckCollisionPointRec(mousePosition, e.button)) {
      std::println("ui::draw || hovering {}", e.name);
    }
  }

  DrawText("Nowrd", GetScreenWidth() / 2, GetScreenHeight() / 2, 42, WHITE);
}

void debug() {}
}  // namespace ui
