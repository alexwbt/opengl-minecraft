#include "pch.h"
#include "shader.h"
#include "file.h"

namespace shader
{
    GLuint CreateShader(const std::string& path, GLenum type)
    {
        GLuint id = glCreateShader(type);

        const char* source_code = util::ReadFile(path).c_str();
        glShaderSource(id, 1, &source_code, NULL);

        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char log[512] = {};
            glGetShaderInfoLog(id, sizeof(log), NULL, log);
            std::cout << log << std::endl;
            throw std::runtime_error("Failed to compile shader (" + path + ")");
        }
    }

    Shader::Shader(const std::string& vertex, const std::string& fragment)
    {
        program_id_ = glCreateProgram();

        auto vertex_shader = CreateShader(vertex, GL_VERTEX_SHADER);
        auto fragment_shader = CreateShader(fragment, GL_FRAGMENT_SHADER);

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
}
