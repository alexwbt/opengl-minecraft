#include "pch.h"
#include "phong-shader.h"

namespace game
{
    PhongShader::PhongShader() : ShaderProgram(
        { {GL_VERTEX_SHADER, "res/shaders/phong.vs"},
        {GL_FRAGMENT_SHADER, "res/shaders/phong.fs"} }
    ) {}

    void PhongShader::UseLight(std::shared_ptr<gl::Light> light, int i)
    {
        switch (light->type)
        {
        case gl::LightType::SUN:
            SetVec3(("sunLights[" + std::to_string(i) + "].direction"), light->direction);
            SetVec3(("sunLights[" + std::to_string(i) + "].ambient"), light->ambient);
            SetVec3(("sunLights[" + std::to_string(i) + "].diffuse"), light->diffuse);
            SetVec3(("sunLights[" + std::to_string(i) + "].specular"), light->specular);
            break;
        case gl::LightType::POINT:
            SetVec3(("lights[" + std::to_string(i) + "].position"), light->position);
            SetVec3(("lights[" + std::to_string(i) + "].ambient"), light->ambient);
            SetVec3(("lights[" + std::to_string(i) + "].diffuse"), light->diffuse);
            SetVec3(("lights[" + std::to_string(i) + "].specular"), light->specular);
            SetFloat(("lights[" + std::to_string(i) + "].constant"), light->constant);
            SetFloat(("lights[" + std::to_string(i) + "].linear"), light->linear);
            SetFloat(("lights[" + std::to_string(i) + "].quadratic"), light->quadratic);
            break;
        case gl::LightType::SPOT:
            SetVec3(("spotLights[" + std::to_string(i) + "].direction"), light->direction);
            SetVec3(("spotLights[" + std::to_string(i) + "].position"), light->position);
            SetVec3(("spotLights[" + std::to_string(i) + "].ambient"), light->ambient);
            SetVec3(("spotLights[" + std::to_string(i) + "].diffuse"), light->diffuse);
            SetVec3(("spotLights[" + std::to_string(i) + "].specular"), light->specular);
            SetFloat(("spotLights[" + std::to_string(i) + "].constant"), light->constant);
            SetFloat(("spotLights[" + std::to_string(i) + "].linear"), light->linear);
            SetFloat(("spotLights[" + std::to_string(i) + "].quadratic"), light->quadratic);
            SetFloat(("spotLights[" + std::to_string(i) + "].cutOff"), light->cutOff);
            SetFloat(("spotLights[" + std::to_string(i) + "].outerCutOff"), light->outerCutOff);
            break;
        }
    }

    void PhongShader::Use(const ShaderProgram::Uniforms& uniforms)
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

    void PhongShader::EnableAttributes()
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, pos));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, uv));
    }
}
