#include "pch.h"

#include "object.h"
#include "chunk.h"

namespace game
{
    Object::Object(uint32_t id)
        : id_(id)
    {}

    void Object::SetMesh(std::shared_ptr<gl::Mesh> mesh)
    {
        mesh_ = std::move(mesh);
    }

    void Object::Update()
    {

    }

    void Object::Render()
    {
        if (!mesh_) return;
        //mesh_->Render();
    }
}
