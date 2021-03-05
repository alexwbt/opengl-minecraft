#pragma once

namespace gl
{
    class Texture
    {
    public:
        static std::shared_ptr<Texture> Load2DTexture(const std::string& path);
        static std::shared_ptr<Texture> LoadCubemapTexture(std::vector<std::string>& paths);

    private:
        uint32_t id_;

        GLenum type_;

    public:
        Texture(uint32_t id, GLenum type);
        ~Texture();

        void Use();
    };
}
