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
            : game_(game), id_(game->NextId()), position_(0)
        {}

        virtual ~Object() {}

        uint32_t id() const { return id_; }
        glm::vec3 position() const { return position_; }

        void SetModel(std::shared_ptr<gl::Model> model) { model_ = std::move(model); }
        void SetPosition(const glm::vec3& pos) { position_ = pos; }

        virtual void Update()
        {}

        virtual void Render(const RenderInfo& info) = 0;
    };
}
