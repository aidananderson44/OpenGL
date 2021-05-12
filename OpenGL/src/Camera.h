#pragma once
#include "glm/glm.hpp"
#include "Window.h"
class Camera
{
public:
	Camera();
	void Look(float dx, float dy);

	void MoveTo(const glm::vec3& position);
	void LookAt(const glm::vec3& position);

	void Integrate(float dt);
	void SetAspectRatio(float aspectRation);
	void SetWindowInput(Window::Key key, Window::Action action);

	glm::mat4 GetViewMatrix() const;
	const glm::mat4& GetProjectionMatrix() const;
	const glm::vec3& GetPosition() const;

private:
	float aspectRatio = 4.0f / 3.0f;
	glm::vec3 GetDirection() const;
	float sensitivity = 0.001f;
	float moveSensitivity = 0.01f;
	glm::vec3 position = glm::vec3(0, 0, 0);
	float theta = 0, phi = 0;
	float thetaVelocity = 0, phiVelocity = 0;

	glm::vec3 up = glm::vec3(0, 1, 0);
	const glm::vec4 forward = glm::vec4(0, 0, -1, 0);
	bool strafeLeft = false, strafeRight = false;
	bool moveForward = false, moveBackward = false;
	bool flyUp = false, flyDown = false;


	
	glm::mat4 projection;
};

