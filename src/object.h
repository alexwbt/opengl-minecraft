#pragma once

#include "mesh.h"

namespace game
{
    class Object
    {
    private:
        uint32_t id_;

        std::shared_ptr<gl::Mesh> mesh_ = nullptr;

        glm::vec3 position;


    public:
        Object(uint32_t id);
        virtual ~Object() {}

        uint32_t id() const { return id_; }

        void SetMesh(std::shared_ptr<gl::Mesh> mesh);

        void Update();
        void Render();
    };
}
