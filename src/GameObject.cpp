#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>  // For transformations
#include <glm/gtc/type_ptr.hpp>  // For glm::value_ptr
#include <GL/glew.h>  // OpenGL functions

// Constructor: Initialize the GameObject's transformation properties and create VAO, VBO
GameObject::GameObject(glm::vec3 startPosition, glm::vec3 startRotation, glm::vec3 startScale)
        : position(startPosition), rotation(startRotation), scale(startScale) {
    // Initialize VAO and VBO here (for example purposes)
    GLfloat vertices[] = {
            // Example cube vertices (you should replace this with your actual object data)
            -0.5f, -0.5f, -0.5f,  // Front-bottom-left
            0.5f, -0.5f, -0.5f,   // Front-bottom-right
            0.5f, 0.5f, -0.5f,    // Front-top-right
            -0.5f, 0.5f, -0.5f,   // Front-top-left
            -0.5f, -0.5f, 0.5f,   // Back-bottom-left
            0.5f, -0.5f, 0.5f,    // Back-bottom-right
            0.5f, 0.5f, 0.5f,     // Back-top-right
            -0.5f, 0.5f, 0.5f     // Back-top-left
            // Add other vertices for a cube (if you're rendering a cube, otherwise replace with your object)
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Assuming the vertex positions are in the first attribute (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Update the object's transformation (position, rotation, scale)
void GameObject::update() {
    // Create a model matrix for the object based on position, rotation, and scale
    model = glm::mat4(1.0f);  // Identity matrix

    // Apply the position
    model = glm::translate(model, position);

    // Apply the rotation (assuming it's Euler angles for simplicity)
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));  // X-axis rotation
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));  // Y-axis rotation
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));  // Z-axis rotation

    // Apply the scale
    model = glm::scale(model, scale);
}

// Render the object (bind buffers, shaders, etc.)
void GameObject::render(GLuint shaderProgram) {
    // Make sure the shader program is in use before passing uniforms
    glUseProgram(shaderProgram);

    // Update the transformation matrix for the object
    update();

    // Get the location of the model matrix uniform in the shader program
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");

    // Pass the model matrix to the shader
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));  // glm::value_ptr(model)

    // Bind the object's VAO and draw it
    glBindVertexArray(VAO);  // Use the VAO
    glDrawArrays(GL_TRIANGLES, 0, 36);  // Example: Draw a cube with 36 vertices (adjust for your object)
    glBindVertexArray(0);  // Unbind the VAO
}
