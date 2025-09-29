#pragma once

#include <raylib.h>

#include <vector>

#include "player.hpp"

namespace Objects {
struct Transform {
  Vector3 position;
  Vector3 scale;
  Color color;
  virtual bool collidesWithPlayer(Player &p) = 0;
};
struct Rectangle : Transform {
  Vector3 size;

  Rectangle(Vector3 pos, Vector3 scl, Color col, Vector3 sz) {
    position = pos;
    scale = scl;
    color = col;
    size = sz;
  }

  bool collidesWithPlayer(Player &p) override {
    BoundingBox playerBox = {
        (Vector3){p.position.x - p.scale.x / 2, p.position.y - p.scale.y / 2,
                  p.position.z - p.scale.z / 2},
        (Vector3){p.position.x + p.scale.x / 2, p.position.y + p.scale.y / 2,
                  p.position.z + p.scale.z / 2}};
    BoundingBox objectBox = {(Vector3){position.x - size.x / 2,
                                      position.y - size.y / 2,
                                      position.z - size.z / 2},
                             (Vector3){position.x + size.x / 2,
                                      position.y + size.y / 2,
                                      position.z + size.z / 2}};
    return CheckCollisionBoxes(playerBox, objectBox);
  }
};
struct Sphere : Transform {
  float radius;

  Sphere(Vector3 pos, Vector3 scl, Color col, float rad) {
    position = pos;
    scale = scl;
    color = col;
    radius = rad;
  }

  bool collidesWithPlayer(Player &p) override {
    BoundingBox playerBox = {
        (Vector3){p.position.x - p.scale.x / 2, p.position.y - p.scale.y / 2,
                  p.position.z - p.scale.z / 2},
        (Vector3){p.position.x + p.scale.x / 2, p.position.y + p.scale.y / 2,
                  p.position.z + p.scale.z / 2}};
    return CheckCollisionBoxSphere(playerBox, position, radius);
  };
};
}  // namespace Objects

struct World {
  std::vector<Objects::Transform *> objs;
};

namespace world {
World init();
void resolveCollisionsXZ(Player &p, World &w);
void resolveCollisionsY(Player &p, World &w);
void draw(World &w);
}  // namespace world