#pragma once

#include "shader.h"
#include "mesh.h"

namespace game
{
    class Object
    {
    private:
        std::shared_ptr<shader::Shader> shader_ = nullptr;
        std::shared_ptr<gl::Mesh> mesh_ = nullptr;

        glm::vec3 position;

    public:
        virtual ~Object() {}

        void SetShader(std::shared_ptr<shader::Shader> shader);
        void SetMesh(std::shared_ptr<gl::Mesh> mesh);

        void Update();
        void Render();
    };
}
