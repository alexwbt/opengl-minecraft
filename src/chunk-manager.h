#pragma once

namespace game
{
    static constexpr float kUnloadRange = 8.0f;
    static constexpr float kLoadRange = 8.0f;
    static constexpr float kLoadRangeY = 2.0f;

    static std::list<glm::vec3> GetLoadOrder()
    {
        std::list<glm::vec3> load_order;
        for (float x = -kLoadRange; x <= kLoadRange; x++)
            for (float y = -kLoadRangeY; y <= kLoadRangeY; y++)
                for (float z = -kLoadRange; z <= kLoadRange; z++)
                    load_order.push_back({ x, y, z });
        load_order.sort([](const glm::vec3& a, const glm::vec3& b) { return glm::length2(a) < glm::length2(b); });
        return load_order;
    }

    static std::list<glm::vec3> chunk_load_order = GetLoadOrder();

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
    private:
        Game* game_;
        std::unordered_map<glm::vec3, std::shared_ptr<Chunk>, KeyFuncs, KeyFuncs> chunks_;

        glm::vec3 load_chunk_pos_{0};

        std::shared_ptr<util::ThreadPool> thread_pool_;

    public:
        ChunkManager(Game* game)
            : game_(game), thread_pool_(std::make_shared<util::ThreadPool>(3))
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
            for (auto& offset : chunk_load_order)
            {
                glm::vec3 pos = load_chunk_pos_ + offset;
                auto pair = chunks_.find(pos);
                if (pair == chunks_.end())
                {
                    auto chunk = std::make_shared<Chunk>(game_, pos, thread_pool_);
                    chunk->Generate();
                    chunks_.insert({ pos, chunk });
                }
                else pair->second->Load();
            }

            for (auto& it : chunks_)
            {
                float distance = glm::distance(it.first, load_chunk_pos_);
                if (distance < kLoadRange)
                    it.second->Update();
                else if (distance >= kUnloadRange)
                    it.second->Unload();
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
