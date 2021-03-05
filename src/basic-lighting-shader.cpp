#include "pch.h"
#include "basic-lighting-shader.h"

namespace gl
{
    BasicLightingShader::BasicLightingShader()
        : Shader("res/shaders/basic-lighting.vs", "res/shaders/basic-lighting.fs")
    {}

    void BasicLightingShader::Use(Shader::Uniforms* uniforms)
    {
        UseProgram();

        auto data = dynamic_cast<Uniforms*>(uniforms);
        if (!data) return;

        int sizes[3] = { 0, 0, 0 };
        for (auto& light : data->lights)
        {
            int type = (int)(light->type);
            UseLight(std::move(light), sizes[type]);
            sizes[type]++;
        }
        SetInt("sunLights_size", sizes[0]);
        SetInt("lights_size", sizes[1]);
        SetInt("spotLights_size", sizes[2]);

        SetVec3("cameraPos", data->camera_pos);

        SetInt("diffuseMap", data->diffuse_map);
        SetFloat("specular", data->specular);
        SetFloat("shininess", data->shininess);

        SetMat4("mvp", data->mvp);
        SetMat4("model", data->model);
    }

    void BasicLightingShader::EnableAttributes()
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, pos));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, uv));
    }
}
