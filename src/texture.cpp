#include "pch.h"
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace gl
{
    std::shared_ptr<Texture> Texture::Load2DTexture(const std::string& path)
    {
        uint32_t id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else throw std::runtime_error("Failed to load texture " + path);
        stbi_image_free(data);

        return std::make_shared<Texture>(id, GL_TEXTURE_2D);
    }

    std::shared_ptr<Texture> Texture::LoadCubemapTexture(std::vector<std::string>& paths)
    {
        static constexpr int kSides = 6;
        if (paths.size() != kSides)
            throw std::runtime_error("Failed to create cubemap. Invalid paths param.");

        uint32_t id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        int width, height, nrChannels;
        stbi_uc* data;
        for (int i = 0; i < kSides; i++)
        {
            data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, 0);
            if (!data) throw std::runtime_error("Failed to load texture " + paths[i]);
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }

        return std::make_shared<Texture>(id, GL_TEXTURE_CUBE_MAP);
    }

    Texture::Texture(uint32_t id, GLenum type)
        : id_(id), type_(type)
    {}

    Texture::~Texture()
    {
        glDeleteTextures(1, &id_);
    }

    void Texture::Use()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(type_, id_);
    }
}
