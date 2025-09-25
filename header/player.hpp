#pragma once

#include <raylib.h>

#include "camera.hpp"

struct Player {
  Vector3 position;
  Vector3 velocity;
  Vector3 scale;
  Cam cam;
  float healthMax;
  float health;
  float rotation;
  float rotationSpeed;
  float speed;
  float runSpeed;
  Model model;
  Color modelColor = WHITE;
};

namespace PlayerDefaults {
const Vector3 Position = {0, 10, 0};
const Vector3 Scale = {1, 1, 1};
const float MaxHealth = 100;
const float Rotation = 0;
const float RotationSpeed = 7;
const float Speed = 4;
const float RunSpeed = 8;
};  // namespace PlayerDefaults

namespace player {
Player init_player();

void draw(Player &p);
void update(Player &p, float deltaTime);
void updateCamera(Player &p, float deltaTime);

void debug(Player &p);
}  // namespace player
