#include "pch.h"
#include "object.h"

namespace game
{
    void Object::SetShader(std::shared_ptr<shader::Shader> shader)
    {
        shader_ = std::move(shader);
    }

    void Object::SetMesh(std::shared_ptr<gl::Mesh> mesh)
    {
        mesh_ = std::move(mesh);
    }

    void Object::Update()
    {

    }

    void Object::Render()
    {
        if (!mesh_ || !shader_)
            return;

        shader_->Use();
        mesh_->Render();
    }
}
