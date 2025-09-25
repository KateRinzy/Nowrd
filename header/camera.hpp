#pragma once

#include <raylib.h>
struct Cam {
  Camera3D camera;
  Vector3 offset;
  float rotationSpeed;
  float distanceFromPlayer;
  float cameraSpeed;
};

namespace CameraDefaults {
const Camera3D Camera = {{0, 3, -5}, {0, 0, 0}, {0, 1, 0}, 80, CAMERA_PERSPECTIVE};
const Vector3 CameraOffset = {0, 2, -5};
const float DistancePlayerCamera = 3;
const float RotationSpeed = 1. / 360.;
const float CameraSpeed = 20;
}  // namespace CameraDefaults

namespace cam {
Cam init();
void debug(Cam &cam);
}  // namespace cam
