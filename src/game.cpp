#include "pch.h"
#include "game.h"

// gl
#include "model.h"
#include "ray.h"

// shaders
#include "phong-shader.h"
#include "skybox-shader.h"
#include "debug-shader.h"
#include "lightning-shader.h"

struct RenderInfo final
{
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 pv;
};

#include "debug-render.h"

// game
#include "object.h"
#include "skybox.h"
#include "lightning.h"

#include "perlin-noise.h"
#include "thread-pool.h"
#include "chunk.h"
#include "chunk-manager.h"
#include "chunk-collider.h"

#include "entity.h"
#include "entity-controller.h"

namespace game
{
    std::map<Textures, std::shared_ptr<gl::Texture>> Game::textures;
    std::map<Shaders, std::shared_ptr<gl::ShaderProgram>> Game::shaders;

    void Game::InitShaders()
    {
        shaders.insert({ Shaders::kPhong, std::make_shared<PhongShader>() });
        shaders.insert({ Shaders::kSkybox, std::make_shared<SkyboxShader>() });
        shaders.insert({ Shaders::kDebug, std::make_shared<DebugShader>() });
        shaders.insert({ Shaders::kLightning, std::make_shared<LightningShader>() });
    }

    void Game::InitTextures()
    {
        textures.insert({ Textures::kChunk, gl::Texture::Load2DTexture("res/textures/chunk.png", GL_RGBA) });

        std::vector<std::string> skybox_paths{
            "res/textures/void/right.png",
            "res/textures/void/left.png",
            "res/textures/void/top.png",
            "res/textures/void/bottom.png",
            "res/textures/void/front.png",
            "res/textures/void/back.png"
        };
        textures.insert({ Textures::kSkybox, gl::Texture::LoadCubemapTexture(skybox_paths) });
    }

    std::shared_ptr<gl::ShaderProgram> Game::GetShader(Shaders shader)
    {
        return shaders.find(shader)->second;
    }

    std::shared_ptr<gl::Texture> Game::GetTexture(Textures texture)
    {
        return textures.find(texture)->second;
    }

    Game::Game() :
        camera_(0.1f, 0.1f)
    {}

    void Game::Init(const std::weak_ptr<Game>& game_ref)
    {
        chunk_manager_ = std::make_shared<ChunkManager>(game_ref);

        debug_render_ = std::make_shared<DebugRender>(std::make_shared<DebugShader>());

        controller_ = std::make_shared<EntityController>(game_ref);

        SetSkybox(std::make_shared<game::Skybox>(game_ref));

        gl::LightColor light_color{ glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(1.0f) };
        auto light = std::make_shared<gl::Light>(glm::vec3(0.2f, -1.0f, 1.2f), light_color);
        AddLight(light);

        auto player = std::make_shared<Entity>(game_ref);
        player->SetPosition({ 0, 32, 0 });
        controller_->SetEntity(player);
        following_id_ = player->id();
        Spawn(player);

        std::vector<glm::vec3> points(2);
        points.at(0) = { 0, 32, 0 };
        points.at(1) = { 0, 10, 0 };
        auto lightning = std::make_shared<Lightning>(
            game_ref, points, 10, 4, 0, 0, 0);
        Spawn(lightning);
    }

    void Game::Update(const std::vector<bool>& controls)
    {
        chunk_manager_->Update(camera_.position);
        controller_->Update(camera_, controls);
        for (auto& entity : objects_)
        {
            entity->Update();
            if (entity->id() == following_id_)
                camera_.position = entity->position();
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

        for (auto& entity : objects_)
            entity->Render(info);

        //debug_render_->DrawLine({ 0, 32, 0 }, { 16, 32, 0 }, { 1, 0, 0 });
        //debug_render_->DrawLine({ 0, 32, 0 }, { 0, 48, 0 }, { 0, 1, 0 });
        //debug_render_->DrawLine({ 0, 32, 0 }, { 0, 32, 16 }, { 0, 0, 1 });
        //debug_render_->Render(info);
    }

    void Game::AddLight(std::shared_ptr<gl::Light> light)
    {
        lights_.push_back(std::move(light));
    }

    void Game::Spawn(std::shared_ptr<Object> object)
    {
        objects_.push_back(std::move(object));
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
