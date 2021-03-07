#pragma once

#include "camera.h"
#include "light.h"
#include "shader.h"
#include "texture.h"

namespace game
{
    class Object;
    class Skybox;
    class Chunk;
    class ChunkManager;

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

        std::shared_ptr<ChunkManager> chunk_manager_;

        std::shared_ptr<Skybox> skybox_;

        std::list<std::shared_ptr<gl::Light>> lights_;
        std::list<std::shared_ptr<Object>> objects_;

    public:
        Game();

        void Init();

        void Update();
        void Render(float width, float height);

        void AddLight(std::shared_ptr<gl::Light> light);
        void Spawn(std::shared_ptr<Object> object);

        void SetSkybox(std::shared_ptr<Skybox> skybox);

        std::vector<std::shared_ptr<gl::Light>> GetLights();
        gl::CameraControl& GetCameraControl() { return camera_; }

        gl::Camera camera() const { return camera_; }
    };
}
