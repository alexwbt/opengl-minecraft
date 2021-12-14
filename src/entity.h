#pragma once

namespace game
{
    class Game;

    class Entity
    {
    protected:
        std::weak_ptr<Game> game_;

        uint32_t id_;

        std::shared_ptr<gl::Model> model_ = nullptr;

        glm::vec3 position_;

    public:
        Entity(const std::weak_ptr<Game>& game)
            : game_(game), id_(0), position_(0)
        {
            if (auto game_ptr = game.lock())
                id_ = game_ptr->NextId();
        }

        virtual ~Entity() {}

        uint32_t id() const { return id_; }
        glm::vec3 position() const { return position_; }

        void SetModel(std::shared_ptr<gl::Model> model) { model_ = std::move(model); }
        void SetPosition(const glm::vec3& pos) { position_ = pos; }

        virtual void Update() {}

        virtual void Render(const RenderInfo& info) = 0;
    };
}
