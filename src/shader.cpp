#include "pch.h"
#include "shader.h"
#include "texture.h"

#include "file.h"

namespace gl
{
    GLuint CreateShader(const char* code, GLenum type)
    {
        GLuint id = glCreateShader(type);

        glShaderSource(id, 1, &code, NULL);

        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char log[512] = {};
            glGetShaderInfoLog(id, sizeof(log), NULL, log);
            std::cout << log << std::endl;
            throw std::runtime_error("Failed to compile shader.");
        }
        return id;
    }

    ShaderProgram::ShaderProgram(const std::vector<Shader>& shaders)
    {
        program_id_ = glCreateProgram();

        const auto count = shaders.size();
        auto shader_ids = new GLuint[count];

        for (int i = 0; i < count; i++)
        {
            shader_ids[i] = CreateShader(util::ReadTextFile(shaders[i].source).c_str(), shaders[i].type);
            glAttachShader(program_id_, shader_ids[i]);
        }

        glLinkProgram(program_id_);

        int success;
        glGetProgramiv(program_id_, GL_LINK_STATUS, &success);
        if (!success)
        {
            char log[512] = {};
            glGetProgramInfoLog(program_id_, sizeof(log), NULL, log);
            std::cout << log << std::endl;
            throw std::runtime_error("Failed to link shader program.");
        }

        for (int i = 0; i < count; i++)
            glDeleteShader(shader_ids[i]);

        delete[] shader_ids;
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(program_id_);
    }

    void ShaderProgram::SetBool(const std::string& name, bool value) const { glUniform1i(glGetUniformLocation(program_id_, name.c_str()), (int)value); }
    void ShaderProgram::SetInt(const std::string& name, int value) const { glUniform1i(glGetUniformLocation(program_id_, name.c_str()), value); }
    void ShaderProgram::SetFloat(const std::string& name, float value) const { glUniform1f(glGetUniformLocation(program_id_, name.c_str()), value); }
    void ShaderProgram::SetVec2(const std::string& name, const glm::vec2& value) const { glUniform2fv(glGetUniformLocation(program_id_, name.c_str()), 1, &value[0]); }
    void ShaderProgram::SetVec2(const std::string& name, float x, float y) const { glUniform2f(glGetUniformLocation(program_id_, name.c_str()), x, y); }
    void ShaderProgram::SetVec3(const std::string& name, const glm::vec3& value) const { glUniform3fv(glGetUniformLocation(program_id_, name.c_str()), 1, &value[0]); }
    void ShaderProgram::SetVec3(const std::string& name, float x, float y, float z) const { glUniform3f(glGetUniformLocation(program_id_, name.c_str()), x, y, z); }
    void ShaderProgram::SetVec4(const std::string& name, const glm::vec4& value) const { glUniform4fv(glGetUniformLocation(program_id_, name.c_str()), 1, &value[0]); }
    void ShaderProgram::SetVec4(const std::string& name, float x, float y, float z, float w) const { glUniform4f(glGetUniformLocation(program_id_, name.c_str()), x, y, z, w); }
    void ShaderProgram::SetMat2(const std::string& name, const glm::mat2& mat) const { glUniformMatrix2fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
    void ShaderProgram::SetMat3(const std::string& name, const glm::mat3& mat) const { glUniformMatrix3fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
    void ShaderProgram::SetMat4(const std::string& name, const glm::mat4& mat) const { glUniformMatrix4fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, &mat[0][0]); }

    void ShaderProgram::UseLight(std::shared_ptr<gl::Light> light, int i)
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

    void ShaderProgram::UseProgram()
    {
        glUseProgram(program_id_);
    }
}
