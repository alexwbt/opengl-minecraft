#pragma once

namespace gl
{
    struct Camera
    {
		float yaw = -90.0f;
		float pitch = 0.0f;
		float fov = 80.0f;
		glm::vec3 position = glm::vec3(0);

		glm::vec3 front, right, up;
		glm::mat4 view_matrix;

		Camera()
		{
			Update();
		}

		void Update()
		{
			front = glm::normalize(glm::vec3(
				glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)),
				glm::sin(glm::radians(pitch)),
				glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch))
			));
			right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
			up = glm::normalize(glm::cross(right, front));

			view_matrix = glm::lookAt(position, position + front, up);
		}
    };
}
