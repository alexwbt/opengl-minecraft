#include "pch.h"
#include "game.h"

namespace game
{
    Game::Game()
        : camera_(0.1f, 0.1f)
    {}

    void Game::Update()
    {
        camera_.Update();
        for (auto& object : objects_)
            object->Update();
    }

    void Game::Render(glfw::Dimension dimension)
    {
        glm::mat4 projection = glm::perspective(glm::radians(camera_.fov),
            (float)dimension.width / (float)dimension.height, 0.1f, 100.0f);
        glm::mat4 pv = projection * camera_.view_matrix;
        RenderInfo info{ camera_, pv };

        for (auto& object : objects_)
            object->Render(info);
    }

    void Game::AddLight(std::shared_ptr<gl::Light> light)
    {
        lights_.push_back(std::move(light));
    }

    void Game::Spawn(std::shared_ptr<Object> object)
    {
        objects_.push_back(std::move(object));
    }

    std::vector<std::shared_ptr<gl::Light>> Game::GetLights()
    {
        std::vector<std::shared_ptr<gl::Light>> lights;
        lights.reserve(lights_.size());
        lights.insert(lights.begin(), lights_.begin(), lights_.end());
        return lights;
    }
}
