#pragma once

namespace game
{
    class Chunk : public Object
    {
        static constexpr float kCube[] = {
            // Back face
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, // Bottom-left
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // bottom-right
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // top-right
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // top-right
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // top-left
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, // bottom-left
            // Front face
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, // bottom-left
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, // top-right
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, // bottom-right
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, // top-right
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, // bottom-left
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // top-left
            // Left face
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // top-right
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // bottom-left
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // top-left
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // bottom-left
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // top-right
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // bottom-right
            // Right face
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // top-left
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // top-right
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // bottom-right
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // bottom-right
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // bottom-left
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // top-left
            // Bottom face
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // top-right
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, // bottom-left
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, // top-left
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, // bottom-left
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // top-right
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, // bottom-right
            // Top face
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // top-left
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, // top-right
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // bottom-right
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // bottom-right
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, // bottom-left
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f  // top-left
        };

        static constexpr int kTextures[3][6] = {
            { 0, 0, 0, 0, 0, 0 },
            { 1, 1, 1, 1, 1, 1 },
            { 3, 3, 3, 3, 1, 2 }
        };

    public:
        static constexpr int kSize = 32;

    private:
        std::shared_ptr<util::ThreadPool> thread_pool_;

        glm::vec3 coordinate_;

        uint8_t data_[kSize][kSize][kSize]{};

        struct ChunkData
        {
            uint8_t data[kSize][kSize][kSize];
        };
        std::future<std::shared_ptr<ChunkData>> generate_future_;
        std::future<std::shared_ptr<std::vector<DefaultShader::Vertex>>> load_future_;

        bool generating_ = false;
        bool loading_ = false;
        bool loaded_ = false;

    public:
        Chunk(Game* game, const glm::vec3& coordinate, std::shared_ptr<util::ThreadPool> thread_pool)
            : Object(game), coordinate_(coordinate), thread_pool_(std::move(thread_pool))
        {
            position_ = coordinate * (float)kSize;
        }

        void Update() override
        {
            if (generate_future_.valid() &&
                generate_future_.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
            {
                auto chunk_data = generate_future_.get();
                for (int x = 0; x < kSize; x++)
                    for (int y = 0; y < kSize; y++)
                        for (int z = 0; z < kSize; z++)
                            data_[x][y][z] = chunk_data->data[x][y][z];
                generating_ = false;
                Load();
            }

            if (load_future_.valid() &&
                load_future_.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
            {
                auto vertices = load_future_.get();
                auto texture = Game::GetTexture("chunk");
                auto shader = Game::GetShader("default");
                SetModel(std::make_shared<gl::Model>(*vertices, std::move(shader), std::move(texture)));
                loading_ = false;
                loaded_ = true;
            }
        }

        void Render(const RenderInfo& info) override
        {
            if (!model_) return;
            glm::mat4 model_matrix = glm::mat4(1.0f);
            model_matrix = glm::translate(model_matrix, position_);

            auto lights = game_->GetLights();
            auto pos = game_->camera().position;

            DefaultShader::Uniforms uniforms;
            uniforms.lights = lights;
            uniforms.camera_pos = pos;
            uniforms.diffuse_map = 0;
            uniforms.specular = 0.2f;
            uniforms.shininess = 16.0f;
            uniforms.mvp = info.pv * model_matrix;
            uniforms.model = model_matrix;
            model_->Render(&uniforms);
        }

        bool Collides(const glm::vec3& min, const glm::vec3& max)
        {
            auto chunk_max = position_ + (float)kSize;
            if (!((min.x <= chunk_max.x && max.x >= position_.x) &&
                (min.y <= chunk_max.y && max.y >= position_.y) &&
                (min.z <= chunk_max.z && max.z >= position_.z)))
                return false;

            auto floor_min = glm::floor(min - position_);
            auto floor_max = glm::floor(max - position_);
            for (int x = (int)floor_min.x; x <= floor_max.x; x++)
                for (int y = (int)floor_min.y; y <= floor_max.y; y++)
                    for (int z = (int)floor_min.z; z <= floor_max.z; z++)
                        if (InBounds(x, y, z) && data_[x][y][z] > 0)
                            return true;
            return false;
        }

        uint8_t GetData(const glm::vec3& pos)
        {
            return GetData((int)pos.x, (int)pos.y, (int)pos.z);
        }

        uint8_t GetData(int x, int y, int z)
        {
            return data_[x][y][z];
        }

        glm::vec3 GetPos()
        {
            return position_;
        }

        void Generate()
        {
            if (generating_) return;
            generating_ = true;
            auto promise = std::make_shared<std::promise<std::shared_ptr<ChunkData>>>();
            auto& position = position_;
            auto task = [promise, position]()
            {
                auto chunk_data = std::make_shared<ChunkData>();
                GenerateData(position, chunk_data->data);
                promise->set_value(std::move(chunk_data));
            };
            thread_pool_->AddTask(task);
            generate_future_ = promise->get_future();
        }

        void Load()
        {
            if (generating_ || loaded_ || loading_) return;
            loading_ = true;
            auto promise = std::make_shared<std::promise<std::shared_ptr<std::vector<DefaultShader::Vertex>>>>();
            auto& position = position_;
            auto chunk_data = std::make_shared<ChunkData>();
            for (int x = 0; x < kSize; x++)
                for (int y = 0; y < kSize; y++)
                    for (int z = 0; z < kSize; z++)
                        chunk_data->data[x][y][z] = data_[x][y][z];
            auto task = [promise, position, chunk_data]()
            {
                auto vertices = GenerateVertices(position, chunk_data->data);
                promise->set_value(std::move(vertices));
            };
            thread_pool_->AddTask(task, true);
            load_future_ = promise->get_future();
        }

        void Unload()
        {
            if (!loaded_ || loading_) return;
            SetModel(nullptr);
            loaded_ = false;
        }

        static bool InBounds(int x, int y, int z)
        {
            return x >= 0 && x < kSize
                && y >= 0 && y < kSize
                && z >= 0 && z < kSize;
        }

    private:
        static bool Noise(const glm::vec3& block_pos)
        {
            static util::PerlinNoise noise;
            static constexpr int kOctaves = 4;
            static constexpr int kLacunarity = 2;
            static constexpr float kPersistance = 0.5f;
            static constexpr float kScale = 40.0f;

            glm::vec3 pos = block_pos / kScale;
            double value = -block_pos.y;
            for (int i = 0; i < kOctaves; i++)
            {
                pos *= pow(kLacunarity, i) * pow(kPersistance, i);
                value += noise.value(pos.x, pos.y, pos.z) * kSize * 0.5;
            }
            return value > kScale * 0.5;
        }

        static void GenerateData(const glm::vec3& position, uint8_t(*data)[kSize][kSize])
        {
            for (int x = 0; x < kSize; x++)
                for (int y = 0; y < kSize; y++)
                    for (int z = 0; z < kSize; z++)
                        data[x][y][z] = Noise(position + glm::vec3(x, y, z)) ? 1 : 0;

            for (int x = 0; x < kSize; x++)
            {
                for (int z = 0; z < kSize; z++)
                {
                    for (int y = kSize - 1; y >= 0; y--)
                    {
                        if (data[x][y][z] == 1)
                        {
                            if (y < kSize - 1 && data[x][y + 1][z] == 0)
                                data[x][y][z] = 3;
                            else if (y == kSize - 1)
                                data[x][y][z] = Noise(position + glm::vec3(x, y + 1, z)) ? 1 : 3;
                            break;
                        }
                    }
                }
            }
        }

        static std::shared_ptr<std::vector<DefaultShader::Vertex>> GenerateVertices(const glm::vec3& position, uint8_t(*data)[kSize][kSize])
        {
            auto vertices = std::make_shared<std::vector<DefaultShader::Vertex>>();
            for (int x = 0; x < kSize; x++)
            {
                for (int y = 0; y < kSize; y++)
                {
                    for (int z = 0; z < kSize; z++)
                    {
                        if (data[x][y][z] == 0) continue;
                        for (int f = 0; f < 6; f++)
                        {
                            int ix = x + (int)kCube[f * 6 * 8 + 3];
                            int iy = y + (int)kCube[f * 6 * 8 + 4];
                            int iz = z + (int)kCube[f * 6 * 8 + 5];

                            uint8_t block = 0;
                            if (!InBounds(ix, iy, iz))
                                block = Noise(position + glm::vec3(ix, iy, iz)) ? 1 : 0;
                            else block = data[ix][iy][iz];

                            if (block > 0) continue;
                            for (int v = 0; v < 6; v++)
                            {
                                int i = f * 6 + v;
                                int tx = kTextures[data[x][y][z] - 1][f] % 10;
                                int ty = kTextures[data[x][y][z] - 1][f] / 10;
                                vertices->push_back({ {
                                        x + kCube[i * 8],
                                        y + kCube[i * 8 + 1],
                                        z + kCube[i * 8 + 2]
                                    }, {
                                        kCube[i * 8 + 3],
                                        kCube[i * 8 + 4],
                                        kCube[i * 8 + 5]
                                    }, {
                                        (tx + (kCube[i * 8 + 6] - 0.5f) * 0.98f + 0.5f) * 0.1f,
                                        (ty + (kCube[i * 8 + 7] - 0.5f) * 0.98f + 0.5f) * 0.1f
                                    } });
                            }
                        }
                    }
                }
            }
            return vertices;
        }
    };
}
