#pragma once

#include "shader.h"

namespace game
{
    class DebugShader : public gl::ShaderProgram
    {
    public:
        struct Uniforms : public ShaderProgram::Uniforms
        {
            glm::mat4 pv;
            glm::vec3 color;
        };

        struct Vertex final
        {
            glm::vec3 pos;
        };

    public:
        DebugShader();

        void Use(const ShaderProgram::Uniforms& uniforms) override;
        void EnableAttributes() override;
    };
}
