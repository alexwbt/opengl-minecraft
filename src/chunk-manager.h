#pragma once

namespace game
{
    class ChunkManager
    {
        struct KeyFuncs
        {
            size_t operator()(const glm::vec3& k)const
            {
                return std::hash<float>()(k.x) ^ std::hash<float>()(k.y) ^ std::hash<float>()(k.z);
            }

            bool operator()(const glm::vec3& a, const glm::vec3& b)const
            {
                return a.x == b.x && a.y == b.y && b.z == a.z;
            }
        };

        static constexpr int kLoadRange = 5;
        static constexpr int kLoadRangeY = 2;
    private:
        Game* game_;
        std::unordered_map<glm::vec3, std::shared_ptr<Chunk>, KeyFuncs, KeyFuncs> chunks_;

        glm::vec3 load_chunk_pos_{0};

    public:
        ChunkManager(Game* game)
            : game_(game)
        {}

        std::shared_ptr<Chunk> GetChunk(const glm::vec3& pos)
        {
            auto it = chunks_.find(pos);
            if (it == chunks_.end())
                return nullptr;
            return it->second;
        }

        void Update(const glm::vec3& load_pos)
        {
            load_chunk_pos_ = glm::floor(load_pos / (float)Chunk::kSize);

            for (int x = -kLoadRange; x <= kLoadRange; x++)
            {
                for (int y = -kLoadRangeY; y <= kLoadRangeY; y++)
                {
                    for (int z = -kLoadRange; z <= kLoadRange; z++)
                    {
                        glm::vec3 pos = load_chunk_pos_ + glm::vec3(x, y, z);
                        if (chunks_.find(pos) == chunks_.end())
                            chunks_.insert({ pos, std::make_shared<Chunk>(game_, pos) });
                    }
                }
            }

            for (auto& it : chunks_)
            {
                if (glm::distance(it.first, load_chunk_pos_) < kLoadRange)
                    it.second->Update();
            }
        }

        void Render(const RenderInfo& info)
        {
            for (auto& it : chunks_)
            {
                if (glm::distance(it.first, load_chunk_pos_) < kLoadRange)
                    it.second->Render(info);
            }
        }
    };
}
