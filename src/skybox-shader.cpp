#include "pch.h"
#include "skybox-shader.h"

namespace game
{
    SkyboxShader::SkyboxShader() : ShaderProgram(
        { {GL_VERTEX_SHADER, "res/shaders/skybox.vs"},
        {GL_FRAGMENT_SHADER, "res/shaders/skybox.fs"} }
    ) {}

    void SkyboxShader::Use(const ShaderProgram::Uniforms& uniforms)
    {
        UseProgram();

        try
        {
            auto data = dynamic_cast<const Uniforms&>(uniforms);

            SetInt("skybox", data.skybox_map);
            SetMat4("pv", data.pv);
        }
        catch (const std::bad_cast& exception)
        {
            std::cout << "Failed to cast debug shader uniform." << std::endl;
            std::cout << exception.what() << std::endl;
        }
    }

    void SkyboxShader::EnableAttributes()
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, pos));
    }
}
