#pragma once

#include "shader.h"
#include "texture.h"

namespace gl
{
	class Model
	{
	private:
		enum class Type
		{
			kVertex,
			kElement
		};

		std::shared_ptr<Shader> shader_;
		std::shared_ptr<Texture> texture_;

		Type type_;

		GLuint vao_id_ = 0;
		GLuint vbo_id_ = 0;
		GLuint ebo_id_ = 0;

		GLsizei vertices_size_ = 0;
		GLsizei indices_size_ = 0;

	public:
		template <typename VertexType>
		Model(
			const std::vector<VertexType> vertices,
			std::shared_ptr<Shader> shader,
			std::shared_ptr<Texture> texture
		) :
			type_(Type::kVertex),
			vertices_size_((GLsizei)vertices.size()),
			shader_(std::move(shader)),
			texture_(std::move(texture))
		{
			glGenVertexArrays(1, &vao_id_);
			glGenBuffers(1, &vbo_id_);

			glBindVertexArray(vao_id_);

			glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
			glBufferData(GL_ARRAY_BUFFER, vertices_size_ * sizeof(VertexType), vertices.data(), GL_STATIC_DRAW);

			shader_->EnableAttributes();

			glBindVertexArray(0);
		}

		~Model()
		{
			if (vao_id_ > 0) glDeleteVertexArrays(1, &vao_id_);
			if (vbo_id_ > 0) glDeleteBuffers(1, &vbo_id_);
			if (ebo_id_ > 0) glDeleteBuffers(1, &ebo_id_);
		}

		void Render(Shader::Uniforms* uniforms)
		{
			shader_->Use(uniforms);
			texture_->Use();

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
