#pragma once

#include "mesh.h"

namespace game
{
    class Object
    {
    private:
        std::shared_ptr<gl::Mesh> mesh_ = nullptr;

        glm::vec3 position;

    public:
        virtual ~Object() {}

        void SetMesh(std::shared_ptr<gl::Mesh> mesh);

        void Update();
        void Render();
    };
}
