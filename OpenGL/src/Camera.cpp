#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cmath>
#define PI 3.14159265358979323846
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define MAX(x, y) (x) > (y) ? (x) : (y)


Camera::Camera()
	:projection(glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 100.0f))
   // :projection(glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 50.0f))
{
}


void Camera::Look(float dx, float dy)
{
    lookAt = false;
    thetaVelocity = dx;
    phiVelocity = dy;
}


glm::mat4 Camera::GetViewMatrix() const
{
    glm::vec3 target;
    if (lookAt)
        target = lookAtVec;
    else
        target = position + GetDirection();
	return glm::lookAt(position, target, up);
}

void Camera::Integrate(float dt)
{
    glm::vec3 direction = GetDirection();
    glm::vec3 perpendicularDirection = glm::normalize(glm::vec3(-direction.z, 0, direction.x));
    glm::vec3 newUp = glm::cross(perpendicularDirection, direction);

    int forwardDirection = 0, flyDirection = 0, strafeDirection = 0;
    if (moveForward && !moveBackward)
        forwardDirection = 1;
    else if (!moveForward && moveBackward)
        forwardDirection = -1;

    if (strafeRight && !strafeLeft)
        strafeDirection = 1;
    else if (!strafeRight && strafeLeft)
        strafeDirection = -1;

    if (flyUp && !flyDown)
        flyDirection = 1;
    else if (!flyUp && flyDown)
        flyDirection = -1;

    glm::vec3 forwardVelocity = direction * (moveSensitivity * forwardDirection);
    glm::vec3 strafeVelocity = perpendicularDirection * (moveSensitivity * strafeDirection);
    glm::vec3 flyVelocity = newUp * (moveSensitivity * flyDirection);
	position += (forwardVelocity + strafeVelocity + flyVelocity) * dt;

    theta = fmodf(theta - thetaVelocity * sensitivity * dt, (float)(2 * PI));
    phi = (float)fmax(-PI / 2 + 0.001, (float)fmin(PI / 2 - 0.001, phi - phiVelocity * sensitivity * dt));
    thetaVelocity = 0;
    phiVelocity = 0;
}

void Camera::SetAspectRatio(float aspectRatio)
{
	this->aspectRatio = aspectRatio;
	if (aspectRatio >= 1)
		projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 100.0f);
	else
		projection = glm::perspective(glm::radians(90.0f), 1.0f / aspectRatio, 0.1f, 100.0f);
}

void Camera::SetWindowInput(Window::Key key, Window::Action action)
{
    switch (key)
    {
    case Window::Key::Forward:
        moveForward = (action != Window::Action::Release);
        break;
    case Window::Key::Backward:
        moveBackward = (action != Window::Action::Release);
        break;
    case Window::Key::StrafeLeft:
        strafeLeft = (action != Window::Action::Release);
        break;
    case Window::Key::StrafeRight:
        strafeRight = (action != Window::Action::Release);
        break;
    case Window::Key::FlyUp:
        flyUp = (action != Window::Action::Release);
        break;
    case Window::Key::FlyDown:
        flyDown = (action != Window::Action::Release);
        break;
    }
}

const glm::vec3& Camera::GetPosition() const
{
    return position;
}

const glm::mat4& Camera::GetProjectionMatrix() const
{
	return projection;
}

glm::vec3 Camera::GetDirection() const
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
    lookAt = true;
    lookAtVec = pointOfInterest;
	glm::vec3 direction = glm::normalize(pointOfInterest - this->position);
	theta = std::atan2f(direction.x, direction.z);
    
	phi = std::atan2f(direction.y, direction.z);
}
