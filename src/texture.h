#pragma once

namespace gl
{
    class Texture final
    {
    public:
        static std::shared_ptr<Texture> Load2DTexture(const std::string& path, int format = GL_RGB);
        static std::shared_ptr<Texture> LoadCubemapTexture(std::vector<std::string>& paths, int format = GL_RGB);

    private:
        uint32_t id_;

        GLenum type_;

    public:
        Texture(uint32_t id, GLenum type);
        ~Texture();

        void Use(int i);
    };
}
