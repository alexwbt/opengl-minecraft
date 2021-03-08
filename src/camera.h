#pragma once

namespace gl
{
    struct Camera
    {
		float yaw = -90.0f;
		float pitch = 0.0f;
		float fov = 80.0f;
		glm::vec3 position{};

		glm::vec3 front, front_side, right, up;
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
			front_side = glm::normalize(glm::vec3(
				glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(0.0f)),
				glm::sin(glm::radians(0.0f)),
				glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(0.0f))
			));
			right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
			up = glm::normalize(glm::cross(right, front));

			view_matrix = glm::lookAt(position, position + front, up);
		}
    };

	class CameraControl : public Camera
	{
	private:
		float camera_speed_;
		float mouse_sensitivity_;

		bool initialized_ = false;
		float mouse_x = 0;
		float mouse_y = 0;

	public:
		CameraControl(float camera_speed, float mouse_sensitivity)
			: camera_speed_(camera_speed), mouse_sensitivity_(mouse_sensitivity)
		{}

		void UpdateControls(const std::vector<bool>& controls)
		{
			if (controls.size() < 5) return;
			if (controls[0]) position += camera_speed_ * front;
			if (controls[1]) position -= camera_speed_ * front;
			if (controls[2]) position += camera_speed_ * right;
			if (controls[3]) position -= camera_speed_ * right;
			if (controls[4]) position += camera_speed_ * glm::vec3(0, 1, 0);
			if (controls[5]) position -= camera_speed_ * glm::vec3(0, 1, 0);
		}

		void UpdateMouse(float x, float y)
		{
			if (initialized_)
			{
				yaw += (x - mouse_x) * mouse_sensitivity_;
				pitch += (mouse_y - y) * mouse_sensitivity_;
			}
			initialized_ = true;
			mouse_x = x;
			mouse_y = y;

			if (pitch > 89.0f) pitch = 89.0f;
			if (pitch < -89.0f) pitch = -89.0f;
		}
	};
}
