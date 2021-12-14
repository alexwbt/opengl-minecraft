#pragma once

namespace game
{
    class DebugRender final
    {
        std::shared_ptr<DebugShader> shader_;

        struct Line final
        {
            glm::vec3 a, b, color;
            float width;
        };

        std::vector<Line> lines_;

    public:
        DebugRender(std::shared_ptr<DebugShader> shader)
            : shader_(std::move(shader)) {}

        void Render(const RenderInfo& info)
        {
            RenderLines(info);
        }

        void DrawLine(const glm::vec3& a, const glm::vec3& b, const glm::vec3& color = glm::vec3(1, 0, 0), GLfloat width = 1.0f)
        {
            lines_.push_back({ a, b, color, width });
        }

        void DrawBox(const glm::vec3& pos, const glm::vec3& lengths, const glm::vec3& color = glm::vec3(1, 0, 0), GLfloat width = 1.0f)
        {
            lines_.push_back({ pos, pos + glm::vec3(lengths.x, 0, 0), color, width });
            lines_.push_back({ pos, pos + glm::vec3(0, lengths.y, 0), color, width });
            lines_.push_back({ pos, pos + glm::vec3(0, 0, lengths.z), color, width });
            lines_.push_back({ pos + lengths, pos + glm::vec3(0, lengths.y, lengths.z), color, width });
            lines_.push_back({ pos + lengths, pos + glm::vec3(lengths.x, 0, lengths.z), color, width });
            lines_.push_back({ pos + lengths, pos + glm::vec3(lengths.x, lengths.y, 0), color, width });
            lines_.push_back({ pos + glm::vec3(0, lengths.y, 0), pos + glm::vec3(lengths.x, lengths.y, 0), color, width });
            lines_.push_back({ pos + glm::vec3(0, lengths.y, 0), pos + glm::vec3(0, lengths.y, lengths.z), color, width });
            lines_.push_back({ pos + glm::vec3(lengths.x, 0, lengths.z), pos + glm::vec3(lengths.x, 0, 0), color, width });
            lines_.push_back({ pos + glm::vec3(lengths.x, 0, lengths.z), pos + glm::vec3(0, 0, lengths.z), color, width });
            lines_.push_back({ pos + glm::vec3(lengths.x, lengths.y, 0), pos + glm::vec3(lengths.x, 0, 0), color, width });
            lines_.push_back({ pos + glm::vec3(0, lengths.y, lengths.z), pos + glm::vec3(0, 0, lengths.z), color, width });
        }

    private:
        void RenderLines(const RenderInfo& info)
        {
            int size = (int)lines_.size();
            GLuint* vaos = new GLuint[size];
            GLuint* vbos = new GLuint[size];
            glGenVertexArrays(size, vaos);
            glGenBuffers(size, vbos);

            for (int i = 0; i < size; i++)
            {
                DebugShader::Vertex vertices[2] = { lines_[i].a, lines_[i].b };

                glBindVertexArray(vaos[i]);

                glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);
                glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(DebugShader::Vertex), &vertices[0], GL_STATIC_DRAW);

                shader_->EnableAttributes();

                DebugShader::Uniforms uniforms{};
                uniforms.pv = info.pv;
                uniforms.color = lines_[i].color;
                shader_->Use(uniforms);
                glLineWidth(lines_[i].width);
                glDrawArrays(GL_LINES, 0, 2);
            }

            glDeleteVertexArrays(size, vaos);
            glDeleteBuffers(size, vbos);

            delete[] vaos;
            delete[] vbos;

            lines_.clear();
        }
    };
}
