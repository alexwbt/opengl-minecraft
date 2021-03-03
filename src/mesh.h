#pragma once

#include "shader.h"

namespace gl
{
	class Mesh
	{
	private:
		enum class Type
		{
			kVertex,
			kElement
		};

		std::shared_ptr<shader::Shader> shader_;

		Type type_;

		GLuint vao_id_ = 0;
		GLuint vbo_id_ = 0;
		GLuint ebo_id_ = 0;

		GLsizei vertices_size_ = 0;
		GLsizei indices_size_ = 0;

	public:
		template <typename Shader>
		Mesh(std::shared_ptr<Shader> shader, const std::vector<typename Shader::Vertex> vertices)
			: shader_(std::move(shader)), type_(Type::kVertex), vertices_size_((GLsizei)vertices.size())
		{
			glGenVertexArrays(1, &vao_id_);
			glGenBuffers(1, &vbo_id_);

			glBindVertexArray(vao_id_);

			glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

			shader_->EnableAttributes();

			glBindVertexArray(0);
		}

		template <typename Shader>
		Mesh(std::shared_ptr<Shader> shader, const std::vector<typename Shader::Vertex> vertices, const std::vector<uint32_t> indices)
			: shader_(shader), type_(Type::kElement), vertices_size_((GLsizei)vertices.size()), indices_size_((GLsizei)indices.size())
		{
			glGenVertexArrays(1, &vao_id_);
			glGenBuffers(1, &vbo_id_);
			glGenBuffers(1, &ebo_id_);

			glBindVertexArray(vao_id_);

			glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

			Shader::EnableAttributes();

			glBindVertexArray(0);
		}

		~Mesh()
		{
			if (vao_id_ > 0) glDeleteVertexArrays(1, &vao_id_);
			if (vbo_id_ > 0) glDeleteBuffers(1, &vbo_id_);
			if (ebo_id_ > 0) glDeleteBuffers(1, &ebo_id_);
		}

		void Render(shader::Shader::Uniforms* uniforms)
		{
			shader_->Use(uniforms);

			glBindVertexArray(vao_id_);
			switch (type_)
			{
			case Type::kVertex:
				glDrawArrays(GL_TRIANGLES, 0, vertices_size_);
				break;
			case Type::kElement:
				glDrawElements(GL_TRIANGLES, indices_size_, GL_UNSIGNED_INT, 0);
				break;
			}
		}
	};
}
