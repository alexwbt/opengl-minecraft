#include "pch.h"
#include "debug-shader.h"

namespace game
{
    DebugShader::DebugShader() : ShaderProgram(
        { {GL_VERTEX_SHADER, "res/shaders/debug.vs"},
        {GL_FRAGMENT_SHADER, "res/shaders/debug.fs"} }
    ) {}

    void DebugShader::Use(const ShaderProgram::Uniforms& uniforms)
    {
        UseProgram();

        try
        {
            const auto& data = dynamic_cast<const Uniforms&>(uniforms);

            SetMat4("pv", data.pv);
            SetVec3("color", data.color);
        }
        catch (const std::bad_cast& exception)
        {
            std::cout << "Failed to cast debug shader uniform." << std::endl;
            std::cout << exception.what() << std::endl;
        }
    }

    void DebugShader::EnableAttributes()
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, pos));
    }
}
