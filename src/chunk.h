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
        glm::vec3 coordinate_;

        int data_[kSize][kSize][kSize]{};

        struct ChunkGenerationData
        {
            int chunk_data[kSize][kSize][kSize];
            std::vector<DefaultShader::Vertex> vertices;
        };
        std::future<std::shared_ptr<ChunkGenerationData>> generate_future_;

    public:
        Chunk(Game* game, const glm::vec3& coordinate)
            : Object(game), coordinate_(coordinate)
        {
            position_ = coordinate * (float)kSize;

            generate_future_ = std::async(std::launch::async, std::bind(Chunk::Generate, position_));
        }

        void Update() override
        {
            if (generate_future_.valid())
            {
                auto data = generate_future_.get();
                for (int x = 0; x < kSize; x++)
                    for (int y = 0; y < kSize; y++)
                        for (int z = 0; z < kSize; z++)
                            data_[x][y][z] = data->chunk_data[x][y][z];
                auto texture = Game::GetTexture("chunk");
                auto shader = Game::GetShader("default");
                SetModel(std::make_shared<gl::Model>(data->vertices, std::move(shader), std::move(texture)));
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

    private:
        static std::shared_ptr<ChunkGenerationData> Generate(const glm::vec3& position)
        {
            auto data = std::make_shared<ChunkGenerationData>();
            GenerateData(position, data->chunk_data);
            data->vertices = GenerateModel(data->chunk_data);
            return data;
        }

        static void GenerateData(const glm::vec3& position, int(*data)[kSize][kSize])
        {
            static util::PerlinNoise noise;

            static constexpr int kOctaves = 4;
            static constexpr int kLacunarity = 2;
            static constexpr float kPersistance = 0.5f;
            static constexpr float kScale = 40.0f;

            for (int x = 0; x < kSize; x++)
            {
                for (int y = 0; y < kSize; y++)
                {
                    for (int z = 0; z < kSize; z++)
                    {
                        glm::vec3 pos = (position + glm::vec3(x, y, z)) / kScale;
                        double value = -position.y - y;
                        for (int i = 0; i < kOctaves; i++)
                        {
                            pos *= pow(kLacunarity, i) * pow(kPersistance, i);
                            value += noise.value(pos.x, pos.y, pos.z) * kSize * 0.5;
                        }

                        data[x][y][z] = value > kSize * 0.5 ? 0 : -1;
                    }
                }
            }

            for (int x = 0; x < kSize; x++)
            {
                for (int y = 0; y < kSize; y++)
                {
                    for (int z = 0; z < kSize; z++)
                    {
                        if (data[x][y][z] == 0)
                        {
                            if (y < kSize - 1 && data[x][y + 1][z] == -1)
                                data[x][y][z] = 2;
                        }
                    }
                }
            }
        }

        static std::vector<DefaultShader::Vertex> GenerateModel(int(*data)[kSize][kSize])
        {
            std::vector<DefaultShader::Vertex> vertices;
            for (int x = 0; x < kSize; x++)
            {
                for (int y = 0; y < kSize; y++)
                {
                    for (int z = 0; z < kSize; z++)
                    {
                        if (data[x][y][z] < 0) continue;
                        for (int f = 0; f < 6; f++)
                        {
                            int ix = x + (int)kCube[f * 6 * 8 + 3];
                            int iy = y + (int)kCube[f * 6 * 8 + 4];
                            int iz = z + (int)kCube[f * 6 * 8 + 5];
                            bool oob = ix < 0 || ix >= kSize || iy < 0 || iy >= kSize || iz < 0 || iz >= kSize;
                            if (!oob && (oob || data[ix][iy][iz] >= 0)) continue;
                            for (int v = 0; v < 6; v++)
                            {
                                int i = f * 6 + v;
                                int tx = kTextures[data[x][y][z]][f] % 10;
                                int ty = kTextures[data[x][y][z]][f] / 10;
                                vertices.push_back({ {
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
