#include "pch.h"
#include "game.h"
#include "camera.h"

//#include "object.h"

namespace game
{
    void Game::Update()
    {
        for (auto& object : objects_)
        {
            object->Update();
        }
    }

    void Game::Render()
    {
        for (auto& object : objects_)
        {
            object->Render();
        }
    }

    void Game::AddLight(std::shared_ptr<gl::Light> light)
    {
        lights_.push_back(light);
    }

    void Game::Spawn(std::shared_ptr<Object> object)
    {
        objects_.push_back(object);
    }
}
