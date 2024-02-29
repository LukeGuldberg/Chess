#pragma once

class Graphics;

class Camera
{
public:
    Camera(Graphics &graphics, int tile_size);

    Graphics &graphics;
    int tile_size;
};