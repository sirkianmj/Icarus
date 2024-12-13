#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>  // For glm::lookAt, glm::perspective
#include <glm/gtc/type_ptr.hpp>  // For glm::value_ptr (if needed for passing to shaders)

Camera::Camera(glm::vec3 startPos)
        : position(startPos), front(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
          pitch(0.0f), yaw(-90.0f), movementSpeed(2.5f), mouseSensitivity(0.1f), fov(45.0f) {}

// Method to handle keyboard input and update the camera position
void Camera::moveCamera(float deltaTime, bool forward, bool backward, bool left, bool right) {
    float velocity = movementSpeed * deltaTime;
    if (forward) position += front * velocity;
    if (backward) position -= front * velocity;
    if (left) position -= glm::normalize(glm::cross(front, up)) * velocity;
    if (right) position += glm::normalize(glm::cross(front, up)) * velocity;
}

// Method to update the camera's direction based on mouse movement
void Camera::updateCameraDirection(float offsetX, float offsetY) {
    yaw += offsetX * mouseSensitivity;
    pitch -= offsetY * mouseSensitivity;

    // Prevent camera flipping
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // Update front vector based on pitch and yaw
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
}

// Method to get the view matrix for the camera
glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

// Method to get the projection matrix (perspective) for the camera
glm::mat4 Camera::getProjectionMatrix(float screenWidth, float screenHeight) {
    return glm::perspective(glm::radians(fov), screenWidth / screenHeight, 0.1f, 100.0f);
}
