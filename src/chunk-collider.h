#pragma once

namespace game
{
    struct ChunkCollider
    {
        float front = 0.5f; // -z
        float back = 0.5f; // z

        float top = 0.5f; // y
        float bottom = 1.5f; // -y

        float left = 0.5f; // -x
        float right = 0.5f; // x

        bool Collides(const glm::vec3& pos, Game* game)
        {
            glm::vec3 tmp_pos = pos;

            tmp_pos.z -= front;
            if (PointInBlock(tmp_pos, game))
                return true;
            tmp_pos.z += front;
            tmp_pos.z += back;
            if (PointInBlock(tmp_pos, game))
                return true;
            tmp_pos.z -= back;

            tmp_pos.y += top;
            if (PointInBlock(tmp_pos, game))
                return true;
            tmp_pos.y -= top;
            tmp_pos.y -= bottom;
            if (PointInBlock(tmp_pos, game))
                return true;
            tmp_pos.y += bottom;

            tmp_pos.x -= left;
            if (PointInBlock(tmp_pos, game))
                return true;
            tmp_pos.x += left;
            tmp_pos.x += right;
            if (PointInBlock(tmp_pos, game))
                return true;
            tmp_pos.x -= right;

            return false;
        }

    private:
        bool PointInBlock(const glm::vec3& pos, Game* game)
        {
            auto chunk = game->GetChunk(glm::floor(pos / (float)Chunk::kSize));
            if (!chunk) return true;
            glm::vec3 block_pos = glm::floor(pos - chunk->GetPos());
            return chunk->GetData(block_pos) >= 0;
        }
    };
}
