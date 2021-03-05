#pragma once

#include "camera.h"
#include "light.h"

namespace game
{
    class Object;

    class Game
    {
        gl::CameraControl camera_;

        std::list<std::shared_ptr<gl::Light>> lights_;
        std::list<std::shared_ptr<Object>> objects_;

    public:
        Game();

        void Init();

        void Update();
        void Render(float width, float height);

        void AddLight(std::shared_ptr<gl::Light> light);
        void Spawn(std::shared_ptr<Object> object);

        std::vector<std::shared_ptr<gl::Light>> GetLights();
        gl::CameraControl& GetCameraControl() { return camera_; }

        gl::Camera camera() const { return camera_; }
    };
}
