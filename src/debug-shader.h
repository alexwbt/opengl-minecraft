#pragma once

#include "shader.h"

namespace game
{
    class DebugShader : public gl::Shader
    {
    public:
        struct Uniforms : public Shader::Uniforms
        {
            glm::mat4 pv;
            glm::vec3 color;
        };

        struct Vertex
        {
            glm::vec3 pos;
        };

    public:
        DebugShader();

        void Use(Shader::Uniforms* uniforms) override;
        void EnableAttributes() override;
    };
}
