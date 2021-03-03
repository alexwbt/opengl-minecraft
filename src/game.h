#pragma once

#include "camera.h"
#include "light.h"
#include "object.h"

namespace game
{
    class Game
    {
        gl::Camera camera_;

        std::list<std::shared_ptr<gl::Light>> lights_;
        std::list<std::shared_ptr<Object>> objects_;

    public:
        void Update();
        void Render();

        void AddLight(std::shared_ptr<gl::Light> light);
        void Spawn(std::shared_ptr<Object> object);
    };
}
