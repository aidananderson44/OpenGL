#pragma once
#include "glm/glm.hpp"

class Camera
{
public:
	Camera() {}


	void MoveForward(float amount);
	void Strafe(float amount);
	void Fly(float amount);
	void Look(float dx, float dy);

	void MoveTo(const glm::vec3& position);
	void LookAt(const glm::vec3& position);

	glm::mat4 GetViewMatrix();

private:
	glm::vec3 GetDirection();
	float sensitivity = 0.01f;
	glm::vec3 position = glm::vec3(0, 0, 0);
	float theta = 0, phi = 0;
	glm::vec3 up = glm::vec3(0, 1, 0);
	const glm::vec4 forward = glm::vec4(0, 0, -1, 0);
};

