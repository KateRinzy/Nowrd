#pragma once
#include <raylib.h>

#include <functional>
#include <string>
#include <vector>

struct Game;

struct Element {
  Rectangle button;
  std::string name;
  std::function<void(Game &g)> callback;
  Color normalColor;
  Color hoveredColor;
};

struct UI {
  std::vector<Element> elements = {};
};

namespace ui {
UI init();
void update(Game &g);
void draw(Game &g);
void debug(Game &g);
}  // namespace ui
