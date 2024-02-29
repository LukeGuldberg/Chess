#include "camera.h"
#include "graphics.h"

Camera::Camera(Graphics &graphics, int tile_size)
    : graphics{graphics}, tile_size{tile_size} {}
