#pragma once

namespace game
{
    struct ChunkCollider
    {
        float front = 0.5f; // -z
        float back = 0.5f; // z

        float top = 0.5f; // y
        float bottom = 0.5f; // -y

        float left = 0.5f; // -x
        float right = 0.5f; // x

        bool CollidesWith(int(*data)[Chunk::kSize][Chunk::kSize])
        {

        }
    };
}
