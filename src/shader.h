#pragma once

namespace shader
{
    class Shader
    {
    private:
        GLuint program_id_;

    public:
        Shader(const std::string& vertex, const std::string& fragment);
    };
}
