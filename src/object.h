#pragma once

#include "model.h"
#include "render-info.h"

namespace game
{
    class Game;

    class Object
    {
    protected:
        std::shared_ptr<Game> game_;

        uint32_t id_;

        std::shared_ptr<gl::Model> model_ = nullptr;

        glm::vec3 position_;

    public:
        Object(std::shared_ptr<Game> game);
        virtual ~Object() {}

        uint32_t id() const { return id_; }

        void SetModel(std::shared_ptr<gl::Model> model);

        virtual void Update();
        virtual void Render(const RenderInfo& info) = 0;
    };
}
