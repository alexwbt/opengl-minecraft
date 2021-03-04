#include "pch.h"
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gl
{
    uint32_t Texture::LoadTexture(const std::string& path, GLint format)
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
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else throw std::runtime_error("Failed to load texture " + path);
        stbi_image_free(data);

        return id;
    }

    Texture::Texture(const std::string& path, GLenum type, GLint format)
        : id_(LoadTexture(path, format)), type_(type)
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
