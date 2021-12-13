#pragma once

namespace game
{
    class Skybox : public Object
    {
        static constexpr int kSkyboxVerticesSize = 108;
        static constexpr float kSkyboxVertices[kSkyboxVerticesSize] = {
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };

    public:
        Skybox(const std::weak_ptr<Game>& game)
            : Object(game)
        {
            std::vector<SkyboxShader::Vertex> vertices;
            vertices.reserve(kSkyboxVerticesSize / 3);
            for (int i = 0; i < kSkyboxVerticesSize; i += 3)
                vertices.push_back({ {
                    kSkyboxVertices[i],
                    kSkyboxVertices[i + 1],
                    kSkyboxVertices[i + 2]} });

            auto shader = Game::GetShader("skybox");

            auto textures = std::make_shared<std::vector<std::shared_ptr<gl::Texture>>>(1);
            textures->at(0) = Game::GetTexture("skybox");

            SetModel(std::make_shared<gl::Model>(vertices, std::move(shader), textures));
        }

        void Render(const RenderInfo& info) override
        {
            if (!model_) return;
            SkyboxShader::Uniforms uniforms;

            glm::mat4 view = glm::mat4(glm::mat3(info.view));

            uniforms.pv = info.projection * view;
            uniforms.skybox_map = 0;

            glDepthMask(GL_FALSE);
            glCullFace(GL_BACK);
            model_->Render(uniforms);
            glCullFace(GL_FRONT);
            glDepthMask(GL_TRUE);
        }
    };
}
