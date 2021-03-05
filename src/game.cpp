#include "pch.h"
#include "game.h"

// gl
#include "model.h"
#include "basic-lighting-shader.h"

// game
#include "object.h"
#include "chunk.h"
#include "skybox.h"

namespace game
{
    std::map<std::string, std::shared_ptr<gl::Texture>> Game::textures;
    std::map<std::string, std::shared_ptr<gl::Shader>> Game::shaders;

    void Game::InitShaders()
    {
        shaders.insert({ "basic-lighting", std::make_shared<BasicLightingShader>() });
    }

    void Game::InitTextures()
    {
        textures.insert({ "chunk", gl::Texture::Load2DTexture("res/textures/chunk.png") });

        std::vector<std::string> skybox_paths{
            "res/textures/skybox/right.jpg",
            "res/textures/skybox/left.jpg",
            "res/textures/skybox/top.jpg",
            "res/textures/skybox/bottom.jpg",
            "res/textures/skybox/front.jpg",
            "res/textures/skybox/back.jpg"
        };
        textures.insert({ "skybox", gl::Texture::LoadCubemapTexture(skybox_paths) });
    }

    std::shared_ptr<gl::Shader> Game::GetShader(const std::string& name)
    {
        return std::move(shaders.find(name)->second);
    }

    std::shared_ptr<gl::Texture> Game::GetTexture(const std::string& name)
    {
        return std::move(textures.find(name)->second);
    }

    Game::Game()
        : camera_(0.1f, 0.1f)
    {}

    void Game::Init()
    {
        auto chunk = std::make_shared<game::Chunk>(this);
        Spawn(chunk);

        gl::LightColor light_color{ glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f) };
        auto light = std::make_shared<gl::Light>(glm::vec3(0.2f, -1.0f, 1.2f), light_color);
        AddLight(light);
    }

    void Game::Update()
    {
        camera_.Update();
        for (auto& object : objects_)
            object->Update();
    }

    void Game::Render(float width, float height)
    {
        glm::mat4 projection = glm::perspective(glm::radians(camera_.fov), width / height, 0.1f, 100.0f);
        glm::mat4 pv = projection * camera_.view_matrix;
        
        for (auto& object : objects_)
            object->Render(pv);
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
