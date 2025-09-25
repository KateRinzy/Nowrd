#include "../header/camera.hpp"

#include <raylib.h>

#include <print>

namespace cam {
Cam init() {
  return {
    CameraDefaults::Camera,
    CameraDefaults::CameraOffset,
    CameraDefaults::RotationSpeed,
    CameraDefaults::DistancePlayerCamera,
    CameraDefaults::CameraSpeed
  };
}
void debug(Cam &cam) {
  return;
}
}  // namespace cam
