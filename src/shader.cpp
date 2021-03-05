#include "pch.h"
#include "shader.h"

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

    Shader::Shader(const std::string& vertex, const std::string& fragment)
    {
        program_id_ = glCreateProgram();

        auto vertex_shader = CreateShader(util::ReadTextFile(vertex).c_str(), GL_VERTEX_SHADER);
        auto fragment_shader = CreateShader(util::ReadTextFile(fragment).c_str(), GL_FRAGMENT_SHADER);

        glAttachShader(program_id_, vertex_shader);
        glAttachShader(program_id_, fragment_shader);

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

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(program_id_);
    }

    void Shader::SetBool(const std::string& name, bool value) const { glUniform1i(glGetUniformLocation(program_id_, name.c_str()), (int)value); }
    void Shader::SetInt(const std::string& name, int value) const { glUniform1i(glGetUniformLocation(program_id_, name.c_str()), value); }
    void Shader::SetFloat(const std::string& name, float value) const { glUniform1f(glGetUniformLocation(program_id_, name.c_str()), value); }
    void Shader::SetVec2(const std::string& name, const glm::vec2& value) const { glUniform2fv(glGetUniformLocation(program_id_, name.c_str()), 1, &value[0]); }
    void Shader::SetVec2(const std::string& name, float x, float y) const { glUniform2f(glGetUniformLocation(program_id_, name.c_str()), x, y); }
    void Shader::SetVec3(const std::string& name, const glm::vec3& value) const { glUniform3fv(glGetUniformLocation(program_id_, name.c_str()), 1, &value[0]); }
    void Shader::SetVec3(const std::string& name, float x, float y, float z) const { glUniform3f(glGetUniformLocation(program_id_, name.c_str()), x, y, z); }
    void Shader::SetVec4(const std::string& name, const glm::vec4& value) const { glUniform4fv(glGetUniformLocation(program_id_, name.c_str()), 1, &value[0]); }
    void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const { glUniform4f(glGetUniformLocation(program_id_, name.c_str()), x, y, z, w); }
    void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const { glUniformMatrix2fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
    void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const { glUniformMatrix3fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
    void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const { glUniformMatrix4fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, &mat[0][0]); }

    void Shader::UseLight(std::shared_ptr<gl::Light> light, int i)
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

    void Shader::UseProgram()
    {
        glUseProgram(program_id_);
    }
}
