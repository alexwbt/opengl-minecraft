#pragma once

#include "camera-control.h"
#include "light.h"
#include "model.h"
#include "glfw-manager.h"

#include "render-info.h"

#include "object.h"

namespace game
{
    class Game : public gl::CameraControl
    {
        gl::Camera camera_;

        std::list<std::shared_ptr<gl::Light>> lights_;
        std::list<std::shared_ptr<Object>> objects_;

    public:
        Game();

        void Update();
        void Render(glfw::Dimension dimension);

        void AddLight(std::shared_ptr<gl::Light> light);
        void Spawn(std::shared_ptr<Object> object);

        std::vector<std::shared_ptr<gl::Light>> GetLights();
        gl::Camera& GetCamera() { return camera_; }
    };
}
