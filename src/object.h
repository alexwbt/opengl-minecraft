#pragma once

namespace game
{
    class Game;

    class Object
    {
    protected:
        Game* game_;

        uint32_t id_;

        std::shared_ptr<gl::Model> model_ = nullptr;

        glm::vec3 position_;

    public:
        Object(Game* game)
            : game_(game), id_(0), position_(0)
        {

        }

        virtual ~Object() {}

        uint32_t id() const { return id_; }

        void SetModel(std::shared_ptr<gl::Model> model)
        {
            model_ = std::move(model);
        }

        virtual void Update()
        {

        }

        virtual void Render(const RenderInfo& info) = 0;
    };
}
