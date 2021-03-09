#pragma once

namespace game
{
    struct ChunkCollider
    {
        glm::vec3 n_bounds{ 0.3f, 1.8f, 0.3f };
        glm::vec3 p_bounds{ 0.3f, 0.1f, 0.3f };

        bool Collides(const glm::vec3& origin, Game* game)
        {
            glm::vec3 pos = origin + 0.5f;
            glm::vec3 min = pos - n_bounds;
            glm::vec3 max = pos + p_bounds;
            glm::vec3 chunk_pos = glm::floor(pos / (float)Chunk::kSize);

            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    for (int z = -1; z <= 1; z++)
                    {
                        auto new_chunk_pos = chunk_pos + glm::vec3(x, y, z);
                        auto chunk = game->GetChunk(new_chunk_pos);
                        if (!chunk || chunk->Collides(min, max))
                            return true;
                    }
                }
            }
            return false;
        }

    private:
        bool PointInBlock(const glm::vec3& pos, Game* game)
        {
            auto real_pos = pos + 0.5f;
            auto chunk = game->GetChunk(glm::floor(real_pos / (float)Chunk::kSize));
            if (!chunk) return true;
            glm::vec3 block_pos = glm::floor(real_pos - chunk->GetPos());
            return chunk->GetData(block_pos) >= 0;
        }
    };
}
