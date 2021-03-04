#pragma once

namespace game
{
    class Game;

    class Object
    {
    protected:
        std::shared_ptr<Game> game_;

        uint32_t id_;

        std::shared_ptr<gl::Model> model_ = nullptr;

        glm::vec3 position;


    public:
        Object(std::shared_ptr<Game> game)
            : game_(std::move(game))
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
