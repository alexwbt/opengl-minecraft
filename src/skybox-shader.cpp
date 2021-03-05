#include "pch.h"
#include "skybox-shader.h"

namespace game
{
    SkyboxShader::SkyboxShader()
        : Shader("res/shaders/skybox.vs", "res/shaders/skybox.fs")
    {}

    void SkyboxShader::Use(Shader::Uniforms* uniforms)
    {
        UseProgram();

        auto data = dynamic_cast<Uniforms*>(uniforms);
        if (!data) return;

        SetInt("skybox", data->skybox_map);
        SetMat4("pv", data->pv);
    }

    void SkyboxShader::EnableAttributes()
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, pos));
    }
}
