#pragma once

#include "mesh.h"
#include "basic-lighting-shader.h"

constexpr float cube[] = {
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

constexpr int textures[3][6] = {
    { 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1 },
    { 3, 3, 3, 3, 1, 2 }
};

namespace game
{
    class Chunk : public Object
    {
        static constexpr int kSize = 8;

        int data[kSize][kSize][kSize]{};

        std::shared_ptr<shader::BasicLightingShader> shader_;

        Chunk(std::shared_ptr<shader::BasicLightingShader> shader)
            : shader_(shader)
        {
            RandomData();
            GenerateMesh();
        }

        void RandomData()
        {
            for (int x = 0; x < kSize; x++)
                for (int y = 0; y < kSize; y++)
                    for (int z = 0; z < kSize; z++)
                        data[x][y][z] = (int)(rand() % 4) - 1;
        }

        void GenerateMesh()
        {
            std::vector<shader::BasicLightingShader::Vertex> vertices;
            for (int x = 0; x < kSize; x++)
            {
                for (int y = 0; y < kSize; y++)
                {
                    for (int z = 0; z < kSize; z++)
                    {
                        if (data[x][y][z] < 0) continue;
                        for (int f = 0; f < 6; f++)
                        {
                            int ix = x + (int)cube[f * 6 * 8 + 3];
                            int iy = y + (int)cube[f * 6 * 8 + 4];
                            int iz = z + (int)cube[f * 6 * 8 + 5];
                            bool oob = ix < 0 || ix >= kSize || iy < 0 || iy >= kSize || iz < 0 || iz >= kSize;
                            if (!oob && (oob || data[ix][iy][iz] < 0)) continue;
                            for (int v = 0; v < 6; v++)
                            {
                                int i = f * 6 + v;
                                int tx = textures[data[x][y][z]][f] % 10;
                                int ty = textures[data[x][y][z]][f] / 10;
                                vertices.push_back({
                                    glm::vec3(x + cube[i * 8],
                                    y + cube[i * 8 + 1],
                                    z + cube[i * 8 + 2]),
                                    glm::vec3(cube[i * 8 + 3],
                                    cube[i * 8 + 4],
                                    cube[i * 8 + 5]),
                                    glm::vec2((tx + cube[i * 8 + 6]) * 0.1f,
                                    (ty + cube[i * 8 + 7]) * 0.1f) });
                            }
                        }
                    }
                }
            }

            SetMesh(std::make_shared<gl::Mesh>(shader_, vertices));
        }
    };
}
