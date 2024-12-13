#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  // For glm::lookAt, glm::perspective

class Camera {
public:
    Camera(glm::vec3 startPos);  // Declaration of the constructor

    void moveCamera(float deltaTime, bool forward, bool backward, bool left, bool right);
    void updateCameraDirection(float offsetX, float offsetY);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix(float screenWidth, float screenHeight);

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float pitch;
    float yaw;
    float movementSpeed;
    float mouseSensitivity;
    float fov;
};
