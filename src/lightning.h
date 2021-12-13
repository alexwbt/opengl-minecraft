#pragma once

#include "math.h"

namespace game
{
    class Lightning : public Object
    {
    private:
        std::vector<glm::vec3> init_points_;

        float displacement_;
        int subdivision_;

        float branchRate_;
        float branchRad_;
        float branchLength_;


        std::vector<glm::vec3> points_;
        std::vector<std::unique_ptr<Lightning>> child_branches_;

    public:
        Lightning(
            const std::weak_ptr<Game>& game,
            const std::vector<glm::vec3>& init_points,
            float displacement, int subdivision,
            float branchRate, float branchRad, float branchLength
        ) :
            Object(game),
            init_points_(init_points),
            displacement_(displacement),
            subdivision_(subdivision),
            branchRate_(branchRate),
            branchRad_(branchRad),
            branchLength_(branchLength)
        {
            Generate();
        }

        void Generate() {
            points_ = init_points_;
            std::vector<glm::vec3> mid_points;
            std::vector<glm::vec3> new_points;

            for (int i = 0; i < subdivision_; ++i)
            {
                mid_points.reserve(points_.size());
                for (int j = 1; j < points_.size(); ++j)
                {
                    const auto& start_point = points_[(j - 1)];
                    const auto& end_point = points_[j];

                    glm::vec3 mid_point = (start_point + end_point) * 0.5f + glm::vec3{
                        (util::rand() - 0.5f) * displacement_ * static_cast<float>(pow(0.5f, i + 1)),
                        (util::rand() - 0.5f) * displacement_ * static_cast<float>(pow(0.5f, i + 1)),
                        (util::rand() - 0.5f) * displacement_ * static_cast<float>(pow(0.5f, i + 1))
                    };

                    mid_points.push_back(mid_point);
                }

                new_points.reserve(points_.size() * 2);
                for (int j = 0; j < points_.size() - 1; ++j)
                {
                    new_points.push_back(points_[j]);
                    new_points.push_back(mid_points[j]);
                }
                new_points.push_back(points_.back());

                points_ = std::move(new_points);
                new_points.clear();
                mid_points.clear();
            }

            std::vector<DebugShader::Vertex> vertices(points_.size());
            std::vector<uint32_t> indices(points_.size() * 2 - 2);
            for (int i = 0; i < points_.size(); ++i)
            {
                vertices.at(i) = DebugShader::Vertex{ points_[i] };

                if (i * 2 < indices.size())
                {
                    indices.at(i * 2) = i;
                    indices.at(i * 2 + 1) = i + 1;
                }
            }

            auto shader = Game::GetShader("debug");
            SetModel(std::make_shared<gl::Model>(std::move(vertices), std::move(indices), std::move(shader), nullptr, GL_LINES));
        }

        void Update() override
        {
            Generate();
        }

        void Render(const RenderInfo& info) override
        {
            if (!model_) return;
            glm::mat4 model_matrix = glm::mat4(1.0f);
            model_matrix = glm::translate(model_matrix, position_);

            DebugShader::Uniforms uniforms;
            uniforms.pv = info.pv;
            uniforms.color = glm::vec3(1, 0, 0);
            model_->Render(uniforms);
        }
    };
}
