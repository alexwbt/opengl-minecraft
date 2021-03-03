#pragma once

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

		Type type_;

		GLuint vao_id_;
		GLuint vbo_id_;
		GLuint ebo_id_ = 0;

		GLsizei vertices_size_;
		GLsizei indices_size_ = 0;

	public:
		Mesh(const std::vector<float> vertices);
		Mesh(const std::vector<float> vertices, const std::vector<uint32_t> indices);
		~Mesh();

		void Render();
	};
}
