#include "../header/world.hpp"

namespace world {

World init() {
  World world;
  world.objs.push_back(
      new Objects::Rectangle({0, 0, 0}, {1, 1, 1}, RED, {10, 1, 10}));
  world.objs.push_back(
      new Objects::Sphere({5, 2, 5}, {1, 1, 1}, BLUE, 2.0f));
  world.objs.push_back(
      new Objects::Sphere({0, 1, 5}, {1, 1, 1}, BLUE, 0.5f));
  return world;
}

void resolveCollisionsXZ(Player &p, World &w) {
  for (auto &obj : w.objs) {
    if (obj->collidesWithPlayer(p)) {
      p.position.x = p.prev_position.x;
      p.position.z = p.prev_position.z;
      p.velocity.x = 0;
      p.velocity.z = 0;
    }
  }
}

void resolveCollisionsY(Player &p, World &w) {
  for (auto &obj : w.objs) {
    if (obj->collidesWithPlayer(p)) {
      p.position.y = p.prev_position.y;
      p.velocity.y = 0;
    }
  }
}

void draw(World &w) {
  for (auto &obj : w.objs) {
    if (auto rect = dynamic_cast<Objects::Rectangle *>(obj)) {
      DrawCube(rect->position, rect->size.x, rect->size.y, rect->size.z,
               rect->color);
    } else if (auto sphere = dynamic_cast<Objects::Sphere *>(obj)) {
      DrawSphere(sphere->position, sphere->radius, sphere->color);
    }
  }
}

}  // namespace world
