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
        std::weak_ptr<Game> game_;

        std::shared_ptr<Entity> entity_ = nullptr;

        bool holding_jump_ = false;

        static constexpr int kReach = 5 * 5;
        bool looking_at_block_ = false;
        glm::vec3 looking_at_{ 0 };

    public:
        EntityController(const std::weak_ptr<Game>& game) : game_(game) {}

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

            UpdateLookingAt(camera);
        }

        void UpdateLookingAt(const gl::Camera& camera)
        {
            auto game = game_.lock();
            if (!game) return;

            glm::vec3 chunk_pos = glm::floor(camera.position / (float)Chunk::kSize);

            std::vector<glm::vec3> blocks;
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    for (int z = -1; z <= 1; z++)
                    {
                        auto new_chunk_pos = chunk_pos + glm::vec3(x, y, z);
                        auto chunk = game->GetChunk(new_chunk_pos);
                        if (chunk)
                        {
                            auto new_blocks = chunk->RayInertects(camera.position, camera.front);
                            if (new_blocks)
                                blocks.insert(blocks.end(), new_blocks->begin(), new_blocks->end());
                        }
                    }
                }
            }

            if (blocks.empty()) return;

            looking_at_block_ = false;
            for (auto& block : blocks)
            {
                auto dis = glm::distance2(block, camera.position);
                if (dis <= kReach && (dis < glm::distance2(looking_at_, camera.position) || !looking_at_block_))
                {
                    looking_at_ = block;
                    looking_at_block_ = true;
                }
            }

            if (looking_at_block_)
                game->debug_render()->DrawBox(looking_at_ - 0.5f, glm::vec3(1), { 0.1, 0.1, 0.1 }, 2.0f);
        }
    };
}
