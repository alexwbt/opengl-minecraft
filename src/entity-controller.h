#pragma once

namespace game
{
    class EntityController
    {
    public:
        enum Control
        {
            kForward,
            kBackward,
            kLeft,
            kRight,
            kJump
        };

    private:
        std::shared_ptr<Entity> entity_ = nullptr;

        bool holding_jump_ = false;

    public:
        void SetEntity(std::shared_ptr<Entity> entity)
        {
            entity_ = std::move(entity);
        }

        void Update(const gl::Camera& camera, const std::vector<bool>& controls)
        {
            if (!entity_ || controls.size() < 5) return;

            if (controls[kForward]) entity_->Move(0.1f * camera.front_side);
            if (controls[kBackward]) entity_->Move(-0.1f * camera.front_side);
            if (controls[kLeft]) entity_->Move(0.1f * camera.right);
            if (controls[kRight]) entity_->Move(-0.1f * camera.right);

            if (controls[kJump])
            {
                if (!holding_jump_ && entity_->on_ground())
                    entity_->Push(glm::vec3(0, 0.35f, 0) + entity_->movements() * 0.6f);
                holding_jump_ = true;
            }
            else holding_jump_ = false;
            //if (controls[5]) entity->Move(-0.1f * glm::vec3(0, 1, 0));
        }
    };
}
