#include "pch.h"
#include "debug-shader.h"

namespace game
{
    DebugShader::DebugShader()
        : Shader("res/shaders/debug.vs", "res/shaders/debug.fs")
    {}

    void DebugShader::Use(Shader::Uniforms* uniforms)
    {
        UseProgram();

        auto data = dynamic_cast<Uniforms*>(uniforms);
        if (!data) return;

        SetMat4("pv", data->pv);
        SetVec3("color", data->color);
    }

    void DebugShader::EnableAttributes()
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, pos));
    }
}
