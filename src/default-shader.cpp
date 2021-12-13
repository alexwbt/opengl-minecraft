#include "pch.h"
#include "default-shader.h"
#include "texture.h"

namespace game
{
    DefaultShader::DefaultShader() : ShaderProgram(
        { {GL_VERTEX_SHADER, "res/shaders/default.vs"},
        {GL_FRAGMENT_SHADER, "res/shaders/default.fs"} }
    ) {}

    void DefaultShader::Use(const ShaderProgram::Uniforms& uniforms)
    {
        UseProgram();

        try
        {
            auto data = dynamic_cast<const Uniforms&>(uniforms);

            int sizes[3] = { 0, 0, 0 };
            for (auto& light : data.lights)
            {
                int type = (int)(light->type);
                UseLight(std::move(light), sizes[type]);
                sizes[type]++;
            }
            SetInt("sunLights_size", sizes[0]);
            SetInt("lights_size", sizes[1]);
            SetInt("spotLights_size", sizes[2]);

            SetVec3("cameraPos", data.camera_pos);

            SetInt("diffuseMap", data.diffuse_map);
            SetFloat("specular", data.specular);
            SetFloat("shininess", data.shininess);

            SetMat4("mvp", data.mvp);
            SetMat4("model", data.model);
        }
        catch (const std::bad_cast& exception)
        {
            std::cout << "Failed to cast debug shader uniform." << std::endl;
            std::cout << exception.what() << std::endl;
        }
    }

    void DefaultShader::EnableAttributes()
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, pos));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, uv));
    }
}
