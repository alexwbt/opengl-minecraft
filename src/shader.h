#pragma once

#include "light.h"

namespace gl
{
    class Texture;

    class ShaderProgram
    {
    public:
        struct Uniforms
        {
            virtual ~Uniforms() {}
        };

        struct Vertex
        {
            virtual ~Vertex() {}
        };

        struct Shader
        {
            GLenum type;
            std::string source;
        };

    private:
        GLuint program_id_;

    public:
        ShaderProgram(const std::vector<Shader>& shaders);
        virtual ~ShaderProgram();

        virtual void EnableAttributes() = 0;
        virtual void Use(const Uniforms& uniforms) = 0;

    protected:
        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetVec2(const std::string& name, const glm::vec2& value) const;
        void SetVec2(const std::string& name, float x, float y) const;
        void SetVec3(const std::string& name, const glm::vec3& value) const;
        void SetVec3(const std::string& name, float x, float y, float z) const;
        void SetVec4(const std::string& name, const glm::vec4& value) const;
        void SetVec4(const std::string& name, float x, float y, float z, float w) const;
        void SetMat2(const std::string& name, const glm::mat2& value) const;
        void SetMat3(const std::string& name, const glm::mat3& value) const;
        void SetMat4(const std::string& name, const glm::mat4& value) const;

        void UseLight(std::shared_ptr<gl::Light> light, int i);

        void UseProgram();
    };
}
