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

        static constexpr int kSize = 8;

        int data[kSize][kSize][kSize]{};

        std::shared_ptr<gl::BasicLightingShader> shader_;
        std::shared_ptr<gl::Texture> texture_;

    public:
        Chunk(Game* game, std::shared_ptr<gl::BasicLightingShader> shader, std::shared_ptr<gl::Texture> texture)
            : Object(game), shader_(std::move(shader)), texture_(texture)
        {
            RandomData();
            GenerateModel();
        }

        void Render(const glm::mat4& pv) override
        {
            if (model_)
            {
                glm::mat4 model_matrix = glm::mat4(1.0f);
                model_matrix = glm::translate(model_matrix, position_);

                auto lights = game_->GetLights();
                auto pos = game_->camera().position;

                gl::BasicLightingShader::Uniforms uniforms;
                uniforms.lights = lights;
                uniforms.camera_pos = pos;
                uniforms.diffuse_map = 0;
                uniforms.specular = 0.2f;
                uniforms.shininess = 16.0f;
                uniforms.mvp = pv * model_matrix;
                uniforms.model = model_matrix;
                model_->Render(&uniforms);
            }
        }

    private:
        void RandomData()
        {
            for (int x = 0; x < kSize; x++)
                for (int y = 0; y < kSize; y++)
                    for (int z = 0; z < kSize; z++)
                        data[x][y][z] = rand() % 4 - 1;
        }

        void GenerateModel()
        {
            std::vector<gl::BasicLightingShader::Vertex> vertices;
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
                                        (tx + kCube[i * 8 + 6]) * 0.1f,
                                        (ty + kCube[i * 8 + 7]) * 0.1f
                                    } });
                            }
                        }
                    }
                }
            }
            SetModel(std::make_shared<gl::Model>(vertices, shader_, texture_));
        }
    };
}
