#pragma once

namespace gl
{
    class Texture
    {
    private:
        static uint32_t LoadTexture(const std::string& path, GLint format);

    private:
        uint32_t id_;

        GLenum type_;

    public:
        Texture(const std::string& path, GLenum type, GLint format);
        ~Texture();

        void Use();
    };
}
