#include "pch.h"
#include "lightning-shader.h"

namespace game
{
    LightningShader::LightningShader() : ShaderProgram(
        { {GL_VERTEX_SHADER, "res/shaders/lightning.vs"},
        {GL_GEOMETRY_SHADER, "res/shaders/lightning.gs"},
        {GL_FRAGMENT_SHADER, "res/shaders/lightning.fs"} }
    ) {}

    void LightningShader::Use(const ShaderProgram::Uniforms& uniforms)
    {
        UseProgram();

        try
        {
            auto data = dynamic_cast<const Uniforms&>(uniforms);

            SetMat4("pv", data.pv);
            SetVec3("color", data.color);
        }
        catch (const std::bad_cast& exception)
        {
            std::cout << "Failed to cast debug shader uniform." << std::endl;
            std::cout << exception.what() << std::endl;
        }
    }

    void LightningShader::EnableAttributes()
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, pos));
    }
}
