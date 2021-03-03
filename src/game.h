#pragma once

#include "camera.h"

namespace game
{
    class Game
    {
    public:
        gl::Camera camera;

        void Update();
        void Render();
    };
}
