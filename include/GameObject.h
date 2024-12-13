#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>  // OpenGL functions

class GameObject {
public:
    glm::vec3 position;  // Position of the object in the world
    glm::vec3 rotation;  // Rotation of the object (Euler angles or quaternion)
    glm::vec3 scale;     // Scale of the object
    GLuint VAO, VBO;     // Vertex Array Object and Vertex Buffer Object for rendering
    glm::mat4 model;     // Model matrix for the object

    // Constructor to initialize the object with position, rotation, and scale
    GameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl);

    // Method to update the object's transformation
    void update();

    // Method to render the object (we'll improve this later with shaders and VAOs)
    void render(GLuint shaderProgram);
};