#include "pch.h"
#include "mesh.h"

namespace gl
{
	Mesh::Mesh(const std::vector<float> vertices)
		: type_(Type::kVertex), vertices_size_((GLsizei)vertices.size())
	{
		glGenVertexArrays(1, &vao_id_);
		glGenBuffers(1, &vbo_id_);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		glBindVertexArray(vao_id_);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	}

	Mesh::Mesh(const std::vector<float> vertices, const std::vector<uint32_t> indices)
		: type_(Type::kElement), vertices_size_((GLsizei)vertices.size()), indices_size_((GLsizei)indices.size())
	{
		glGenVertexArrays(1, &vao_id_);
		glGenBuffers(1, &vbo_id_);
		glGenBuffers(1, &ebo_id_);

		glBindVertexArray(vao_id_);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &vao_id_);
		glDeleteBuffers(1, &vbo_id_);

		if (type_ == Type::kElement)
			glDeleteBuffers(1, &ebo_id_);
	}

	void Mesh::Render()
	{
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
}
