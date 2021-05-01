#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cmath>
#define PI 3.14159265358979323846

void Camera::MoveForward(float amount)
{
	position += GetDirection() * amount * sensitivity;
}

void Camera::Strafe(float amount)
{
	glm::vec3 direction = GetDirection();
	glm::vec3 perpendicularDirection(-direction.z, 0, direction.x);
	position += perpendicularDirection * amount * sensitivity;
}

void Camera::Fly(float amount)
{
	position.y += amount * sensitivity;
}

void Camera::Look(float dx, float dy)
{
	theta = fmodf(theta - dx * sensitivity, 2 * PI);
	phi = fmax(-PI / 2, fmin(PI / 2 - 0.001, phi - dy * sensitivity));
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + GetDirection(), up);
}

glm::vec3 Camera::GetDirection()
{
	glm::mat4 rotation = glm::rotate(glm::rotate(glm::mat4(1.0f), theta, glm::vec3(0, 1, 0)), phi, glm::vec3(1, 0, 0));
	return rotation * forward;
}


void Camera::MoveTo(const glm::vec3& position)
{
	this->position = position;
}

void Camera::LookAt(const glm::vec3& pointOfInterest)
{
	glm::vec3 direction = glm::normalize(pointOfInterest - this->position);
	theta = std::atan2f(direction.x, direction.z);
	phi = std::atan2(direction.y, direction.z);
}
