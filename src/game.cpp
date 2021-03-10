#include "pch.h"
#include "game.h"

// gl
#include "model.h"

// shaders
#include "default-shader.h"
#include "skybox-shader.h"
#include "debug-shader.h"

struct RenderInfo
{
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 pv;
};

#include "debug-render.h"

// game
#include "object.h"
#include "skybox.h"

#include "perlin-noise.h"
#include "thread-pool.h"
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

    Game::Game() :
        camera_(0.1f, 0.1f),
        chunk_manager_(std::make_shared<ChunkManager>(this))
    {}

    void Game::Init()
    {
        debug_render_ = std::make_shared<DebugRender>(std::make_shared<DebugShader>());

        SetSkybox(std::make_shared<game::Skybox>(this));

        gl::LightColor light_color{ glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(1.0f) };
        auto light = std::make_shared<gl::Light>(glm::vec3(0.2f, -1.0f, 1.2f), light_color);
        AddLight(light);

        auto player = std::make_shared<Entity>(this);
        player->SetPosition({ 0, 32, 0 });
        player_id_ = player->id();
        Spawn(player);
    }

    void Game::Update(const std::vector<bool>& controls)
    {
        chunk_manager_->Update(camera_.position);
        for (auto& entity : entities_)
        {
            if (entity->id() == player_id_)
            {
                if (controls.size() < 5) return;
                if (controls[0]) entity->Move(0.1f * camera_.front_side);
                if (controls[1]) entity->Move(-0.1f * camera_.front_side);
                if (controls[2]) entity->Move(0.1f * camera_.right);
                if (controls[3]) entity->Move(-0.1f * camera_.right);
                if (controls[4] && entity->on_ground()) entity->Push(glm::vec3(0, 0.35f, 0));
                //if (controls[5]) entity->Move(-0.1f * glm::vec3(0, 1, 0));
            }
            entity->Update();
            if (entity->id() == player_id_)
            {
                camera_.position = entity->position();
            }
        }
        camera_.Update();
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

        debug_render_->DrawLine({ 0, 32, 0 }, { 16, 32, 0 }, { 1, 0, 0 });
        debug_render_->DrawLine({ 0, 32, 0 }, { 0, 48, 0 }, { 0, 1, 0 });
        debug_render_->DrawLine({ 0, 32, 0 }, { 0, 32, 16 }, { 0, 0, 1 });
        debug_render_->Render(info);
    }

    void Game::AddLight(std::shared_ptr<gl::Light> light)
    {
        lights_.push_back(std::move(light));
    }

    void Game::Spawn(std::shared_ptr<Entity> entity)
    {
        entities_.push_back(std::move(entity));
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

    std::shared_ptr<Chunk> Game::GetChunk(const glm::vec3& pos)
    {
        return chunk_manager_->GetChunk(pos);
    }
}
