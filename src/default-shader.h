#pragma once

#include "shader.h"

namespace game
{
    class DefaultShader : public gl::Shader
    {
    public:
        struct Uniforms : public Shader::Uniforms
        {
            std::vector<std::shared_ptr<gl::Light>> lights;
            glm::vec3 camera_pos;
            int diffuse_map;
            float specular;
            float shininess;
            glm::mat4 mvp;
            glm::mat4 model;
        };

        struct Vertex
        {
            glm::vec3 pos;
            glm::vec3 normal;
            glm::vec2 uv;
        };

    public:
        DefaultShader();

        void Use(Shader::Uniforms* uniforms) override;
        void EnableAttributes() override;
    };
}
