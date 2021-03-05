#pragma once

#include "object.h"
#include "basic-lighting-shader.h"

namespace game
{
    class Chunk : public Object
    {
        static constexpr int kSize = 8;

        int data[kSize][kSize][kSize]{};

        std::shared_ptr<gl::BasicLightingShader> shader_;
        std::shared_ptr<gl::Texture> texture_;

    public:
        Chunk(std::shared_ptr<Game> game, std::shared_ptr<gl::BasicLightingShader> shader, std::shared_ptr<gl::Texture> texture);

        void Render(const RenderInfo& info) override;

    private:
        void RandomData();
        void GenerateModel();
    };
}
