#include "pch.h"
#include "object.h"

namespace game
{
    Object::Object(std::shared_ptr<Game> game)
        : game_(std::move(game)), id_(0), position_(0)
    {

    }

    void Object::SetModel(std::shared_ptr<gl::Model> model)
    {
        model_ = std::move(model);
    }

    void Object::Update()
    {

    }
}
