#pragma once

#include "shader.h"

namespace game
{
    class SkyboxShader : public gl::ShaderProgram
    {
    public:
        struct Uniforms : public ShaderProgram::Uniforms
        {
            glm::mat4 pv;
            int skybox_map;
        };

        struct Vertex
        {
            glm::vec3 pos;
        };

    public:
        SkyboxShader();

        void Use(const ShaderProgram::Uniforms& uniforms) override;
        void EnableAttributes() override;
    };
}
