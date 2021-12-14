#pragma once

#include "shader.h"

namespace game
{
    class PhongShader : public gl::ShaderProgram
    {
    public:
        struct Uniforms : public ShaderProgram::Uniforms
        {
            std::vector<std::shared_ptr<gl::Light>> lights;
            glm::vec3 camera_pos;
            int diffuse_map;
            float specular;
            float shininess;
            glm::mat4 mvp;
            glm::mat4 model;
        };

        struct Vertex final
        {
            glm::vec3 pos;
            glm::vec3 normal;
            glm::vec2 uv;
        };

    public:
        PhongShader();

        void EnableAttributes() override;

    private:
        void UseLight(std::shared_ptr<gl::Light> light, int i);
        void Use(const ShaderProgram::Uniforms& uniforms) override;
    };
}
