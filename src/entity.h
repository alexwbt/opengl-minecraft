#pragma once

namespace game
{
    class Entity : public Object
    {
    private:
        ChunkCollider collider_;

        glm::vec3 velocity_;
        glm::vec3 gravity_{0, 9.8f / 60.0f, 0};

    public:
        void Update() override
        {
            velocity_ += gravity_;
            position_ += velocity_;
        }

        virtual void Push(const glm::vec3& force)
        {
            velocity_ += force;
        }
    };
}
