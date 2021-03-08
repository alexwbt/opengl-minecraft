#pragma once

#include "camera.h"
#include "light.h"
#include "shader.h"
#include "texture.h"

namespace game
{
    class Skybox;
    class Chunk;
    class ChunkManager;
    class Entity;
    class DebugRender;

    class Game
    {
    private:
        static std::map<std::string, std::shared_ptr<gl::Texture>> textures;
        static std::map<std::string, std::shared_ptr<gl::Shader>> shaders;

    public:
        static void InitShaders();
        static void InitTextures();
        static std::shared_ptr<gl::Shader> GetShader(const std::string& name);
        static std::shared_ptr<gl::Texture> GetTexture(const std::string& name);

    private:
        gl::CameraControl camera_;

        uint32_t player_id_;

        std::shared_ptr<DebugRender> debug_render_;

        std::shared_ptr<ChunkManager> chunk_manager_;

        std::shared_ptr<Skybox> skybox_;

        std::list<std::shared_ptr<gl::Light>> lights_;
        std::list<std::shared_ptr<Entity>> entities_;

        uint32_t next_id_ = 0;

    public:
        Game();

        void Init();

        void Update(const std::vector<bool>& controls);
        void Render(float width, float height);

        uint32_t NextId() { return ++next_id_; }

        void AddLight(std::shared_ptr<gl::Light> light);
        void Spawn(std::shared_ptr<Entity> entity);

        void SetSkybox(std::shared_ptr<Skybox> skybox);

        std::vector<std::shared_ptr<gl::Light>> GetLights();
        gl::CameraControl& GetCameraControl() { return camera_; }
        std::shared_ptr<Chunk> GetChunk(const glm::vec3& pos);
        std::shared_ptr<DebugRender> debug_render() const { return debug_render_; }

        gl::Camera camera() const { return camera_; }
    };
}
