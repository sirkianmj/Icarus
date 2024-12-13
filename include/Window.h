#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Window {
private:
    sf::RenderWindow window;
    GLuint shaderProgram;
    GLuint VAO, VBO, EBO;
    glm::mat4 model, view, projection;

    void initOpenGL();
    void loadShaders();
    void setupBuffers();
    void renderCube();
    void handleEvents();

public:
    Window();  // Constructor to initialize the window with a title and size
    void runGameLoop();  // Main game loop to run the window and handle events
};
void checkOpenGLError();
#endif
