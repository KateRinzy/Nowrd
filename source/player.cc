#include "../header/player.hpp"

#include <raylib.h>

#include <cmath>
#include <print>

#include "raymath.h"

namespace player {
Player init_player() {
  Cam cam = cam::init();
  // Mesh mesh = GenMeshCube(1, 1, 1);
  std::string filepath = "assets/base_mesh.glb";
  Model model = LoadModel(filepath.c_str());
  Player p = {PlayerDefaults::Position,
              {0, 0, 0},
              PlayerDefaults::Scale,
              cam,
              PlayerDefaults::MaxHealth,
              PlayerDefaults::MaxHealth,
              0,
              PlayerDefaults::RotationSpeed,
              PlayerDefaults::Speed,
              PlayerDefaults::RunSpeed,
              model};
  return p;
}

void draw(Player &p) {
  DrawModelEx(p.model, p.position, {0, 1, 0}, p.rotation, p.scale, WHITE);
  return;
}

void update(Player &p, float deltaTime) {
  Vector3 direction = {0, 0};
  if (IsKeyDown(KeyboardKey::KEY_W)) {
    direction.z -= 1;
  }
  if (IsKeyDown(KeyboardKey::KEY_S)) {
    direction.z += 1;
  }
  if (IsKeyDown(KeyboardKey::KEY_A)) {
    direction.x -= 1;
  }
  if (IsKeyDown(KeyboardKey::KEY_D)) {
    direction.x += 1;
  }

  Vector3 movement = {0, 0};
  if (direction.x != 0 || direction.z != 0) {
    Vector3 camForward = Vector3Normalize(p.cam.camera.target - p.cam.camera.position);
    Vector3 forward = Vector3Normalize(
        {p.cam.camera.target.x - p.cam.camera.position.x, 0, p.cam.camera.target.z - p.cam.camera.position.z});
    Vector3 right = Vector3CrossProduct(forward, p.cam.camera.up);

    movement = Vector3Normalize(forward * -direction.z + right * direction.x);
    float targetRotation = atan2(movement.x, movement.z) * RAD2DEG;

    float deltaAngle = targetRotation - p.rotation;
    while (deltaAngle < -180) {
      deltaAngle += 360;
    }
    while (deltaAngle > 180) {
      deltaAngle -= 360;
    }

    p.rotation += deltaAngle * p.rotationSpeed * deltaTime;
  }

  float speed = p.speed;
  if (IsKeyDown(KEY_LEFT_SHIFT)) {
    speed = p.runSpeed;
  }
  p.velocity.x = movement.x * speed;
  p.velocity.z = movement.z * speed;

  p.velocity.y -= 9.8 * deltaTime;
  p.position += p.velocity * deltaTime;
  float groundLevel = 0;
  if (p.position.y < groundLevel) {
    p.position.y = groundLevel;
    p.velocity.y = 0;
    // p.is_on_ground = true;
  } else {
    // p.is_on_ground = false;
  }
}

void updateCamera(Player &p, float deltaTime) {
  // calculate desired camera position and target
  Vector3 desiredPos = p.position + p.cam.offset;
  Vector3 desiredTarget = p.position;

  // smoothing factor (tune to taste, larger = snappier, smaller = smoother)
  float lerpSpeed = 10.0f;

  // interpolate camera state
  p.cam.camera.position = Vector3Lerp(p.cam.camera.position, desiredPos, lerpSpeed * deltaTime);
  p.cam.camera.target = Vector3Lerp(p.cam.camera.target, desiredTarget, lerpSpeed * deltaTime);

  // rotation with mouse movement
  Vector2 mouseDelta = GetMouseDelta();
  p.cam.offset = Vector3RotateByAxisAngle(p.cam.offset, {0, 1, 0}, -mouseDelta.x * p.cam.rotationSpeed);

  Vector3 new_offset =
      Vector3RotateByAxisAngle(p.cam.offset, Vector3CrossProduct(p.cam.camera.up, Vector3Normalize(p.cam.offset)),
                               -mouseDelta.y * p.cam.rotationSpeed);

  const float maxAngle = 60.0f * DEG2RAD;
  const float minAngle = 10.0f * DEG2RAD;
  float verticalAngle = asinf(Vector3Normalize(new_offset).y);

  if (verticalAngle < maxAngle && verticalAngle > minAngle) {
    p.cam.offset = new_offset;
  }

  // zoom
  p.cam.distanceFromPlayer -= GetMouseWheelMove();
  if (p.cam.distanceFromPlayer < 1) p.cam.distanceFromPlayer = 1;
  p.cam.offset = Vector3Normalize(p.cam.offset) * p.cam.distanceFromPlayer;

  // recompute desired position after zoom/rotation
  desiredPos = p.position + p.cam.offset;
  desiredTarget = p.position;

  // lerp again so zoom/rotation also smooth
  p.cam.camera.position = Vector3Lerp(p.cam.camera.position, desiredPos, lerpSpeed * deltaTime);
  p.cam.camera.target = Vector3Lerp(p.cam.camera.target, desiredTarget, lerpSpeed * deltaTime);
}

void debug(Player &p) { return; }
}  // namespace player
