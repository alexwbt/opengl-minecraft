#pragma once

#include "shader.h"

namespace game
{
    class LightningShader : public gl::ShaderProgram
    {
    public:
        struct Uniforms : public ShaderProgram::Uniforms
        {
            glm::mat4 pv;
            glm::vec3 color;
        };

        struct Vertex
        {
            glm::vec3 pos;
        };

    public:
        LightningShader();

        void EnableAttributes() override;

    private:
        void Use(const ShaderProgram::Uniforms& uniforms) override;
    };
}
