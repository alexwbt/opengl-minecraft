#include "pch.h"
#include "game.h"

// gl
#include "model.h"

// shaders
#include "default-shader.h"
#include "skybox-shader.h"

struct RenderInfo
{
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 pv;
};

// game
#include "object.h"
#include "skybox.h"

#include "perlin-noise.h"
#include "chunk.h"
#include "chunk-manager.h"
#include "chunk-collider.h"

#include "entity.h"

namespace game
{
    std::map<std::string, std::shared_ptr<gl::Texture>> Game::textures;
    std::map<std::string, std::shared_ptr<gl::Shader>> Game::shaders;

    void Game::InitShaders()
    {
        shaders.insert({ "default", std::make_shared<DefaultShader>() });
        shaders.insert({ "skybox", std::make_shared<SkyboxShader>() });
    }

    void Game::InitTextures()
    {
        textures.insert({ "chunk", gl::Texture::Load2DTexture("res/textures/chunk.png", GL_RGBA) });

        std::vector<std::string> skybox_paths{
            "res/textures/void/right.png",
            "res/textures/void/left.png",
            "res/textures/void/top.png",
            "res/textures/void/bottom.png",
            "res/textures/void/front.png",
            "res/textures/void/back.png"
        };
        textures.insert({ "skybox", gl::Texture::LoadCubemapTexture(skybox_paths) });
    }

    std::shared_ptr<gl::Shader> Game::GetShader(const std::string& name)
    {
        return shaders.find(name)->second;
    }

    std::shared_ptr<gl::Texture> Game::GetTexture(const std::string& name)
    {
        return textures.find(name)->second;
    }

    Game::Game()
        : camera_(0.1f, 0.1f), chunk_manager_(std::make_shared<ChunkManager>(this))
    {}

    void Game::Init()
    {
        SetSkybox(std::make_shared<game::Skybox>(this));

        gl::LightColor light_color{ glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(1.0f) };
        auto light = std::make_shared<gl::Light>(glm::vec3(0.2f, -1.0f, 1.2f), light_color);
        AddLight(light);
    }

    void Game::Update()
    {
        camera_.Update();
        chunk_manager_->Update(camera_.position);
        for (auto& entity : entities_)
            entity->Update();
    }

    void Game::Render(float width, float height)
    {
        glm::mat4 projection = glm::perspective(glm::radians(camera_.fov), width / height, 0.1f, 1000.0f);
        glm::mat4 pv = projection * camera_.view_matrix;

        const RenderInfo info{
            projection,
            camera_.view_matrix,
            pv
        };

        skybox_->Render(info);

        chunk_manager_->Render(info);

        for (auto& entity : entities_)
            entity->Render(info);
    }

    void Game::AddLight(std::shared_ptr<gl::Light> light)
    {
        lights_.push_back(std::move(light));
    }

    void Game::Spawn(std::shared_ptr<Object> entity)
    {
        entitys_.push_back(std::move(entity));
    }

    void Game::SetSkybox(std::shared_ptr<Skybox> skybox)
    {
        skybox_ = std::move(skybox);
    }

    std::vector<std::shared_ptr<gl::Light>> Game::GetLights()
    {
        std::vector<std::shared_ptr<gl::Light>> lights;
        lights.reserve(lights_.size());
        lights.insert(lights.begin(), lights_.begin(), lights_.end());
        return lights;
    }
}
