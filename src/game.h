#pragma once

namespace game
{
    class Game
    {
    public:
        engine::Camera camera;

        void Update();
        void Render();
    };
}
