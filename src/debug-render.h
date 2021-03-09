#pragma once

namespace game
{
    class DebugRender
    {
        std::shared_ptr<DebugShader> shader_;

        struct Line
        {
            glm::vec3 a, b, color;
        };

        std::vector<Line> lines_;

    public:
        DebugRender(std::shared_ptr<DebugShader> shader)
            : shader_(std::move(shader)) {}

        void Render(const RenderInfo& info)
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
                shader_->Use(&uniforms);
                glDrawArrays(GL_LINES, 0, 2);
            }

            glDeleteVertexArrays(size, vaos);
            glDeleteBuffers(size, vbos);

            delete[] vaos;
            delete[] vbos;

            lines_.clear();
        }

        void DrawLine(const glm::vec3& a, const glm::vec3& b, const glm::vec3& color = glm::vec3(1, 0, 0))
        {
            lines_.push_back({ a, b, color });
        }
    };
}
