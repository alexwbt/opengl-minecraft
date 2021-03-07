#pragma once

#include "shader.h"

namespace game
{
    class SkyboxShader : public gl::Shader
    {
    public:
        struct Uniforms : public Shader::Uniforms
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

        void Use(Shader::Uniforms* uniforms) override;
        void EnableAttributes() override;
    };
}
