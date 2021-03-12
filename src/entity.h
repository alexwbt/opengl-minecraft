#pragma once

namespace game
{
    class Entity : public Object
    {
    private:
        ChunkCollider collider_;

        static constexpr float kCollisionStep = 0.05f;
        static constexpr float kGravity = 0.03f;

        glm::vec3 velocity_{0};
        glm::vec3 movements_{0};

        float movement_speed_ = 0.2f;

        bool on_ground_ = false;

    public:
        Entity(Game* game) : Object(game) {}

        bool on_ground() const { return on_ground_; }

        void Update() override
        {
            velocity_.y -= kGravity;
            glm::vec3 movement = velocity_;
            if (glm::length2(movements_) > 0)
                movement += glm::normalize(movements_) * movement_speed_ * (on_ground_ ? 1 : 0.5f);
            bool x_done = false;
            bool y_done = false;
            bool z_done = false;
            while (!x_done || !y_done || !z_done)
            {
                if (!x_done && abs(movement.x) >= kCollisionStep)
                {
                    float step = movement.x > 0 ? kCollisionStep : -kCollisionStep;
                    position_.x += step;
                    if (collider_.Collides(position_, game_))
                    {
                        position_.x -= step;
                        x_done = true;
                        velocity_.x = 0;
                    }
                    movement.x -= step;
                }
                else x_done = true;

                if (!y_done && abs(movement.y) >= kCollisionStep)
                {
                    on_ground_ = false;
                    float step = movement.y > 0 ? kCollisionStep : -kCollisionStep;
                    position_.y += step;
                    if (collider_.Collides(position_, game_))
                    {
                        position_.y -= step;
                        y_done = true;
                        if (step < 0) on_ground_ = true;
                        velocity_.y = 0;
                    }
                    movement.y -= step;
                }
                else y_done = true;

                if (!z_done && abs(movement.z) >= kCollisionStep)
                {
                    float step = movement.z > 0 ? kCollisionStep : -kCollisionStep;
                    position_.z += step;
                    if (collider_.Collides(position_, game_))
                    {
                        position_.z -= step;
                        z_done = true;
                        velocity_.z = 0;
                    }
                    movement.z -= step;
                }
                else z_done = true;
            }

            movements_ = glm::vec3(0);
            if (on_ground_)
                velocity_ *= glm::vec3(0.5f);
        }

        void Render(const RenderInfo& info) override
        {}

        void Push(const glm::vec3& force)
        {
            velocity_ += force;
        }

        void Move(const glm::vec3& movement)
        {
            movements_ += movement;
        }

        glm::vec3 movements() const { return movements_; }
    };
}
