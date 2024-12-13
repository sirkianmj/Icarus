#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h> // Must be first
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include <glm/glm.hpp> // For handling 3D math (we'll add glm for matrix transformations)
#include <glm/gtc/matrix_transform.hpp>

class Window {
private:
    sf::RenderWindow window;
    std::string windowTitle;
    int width, height;
    glm::mat4 viewMatrix; // View matrix for camera
    glm::mat4 projectionMatrix; // Projection matrix for 3D perspective
    void handleEvents();
public:
    // Constructor to initialize the window with a title and size
    Window();

    // Display current window properties
    void displayProperties();

    // Handle user input for new title, width, and height
    void handleUserInput();

    // Main game loop to run the window and handle events
    void runGameLoop();

    // Initialize OpenGL settings
    void initOpenGL();

    // Render a basic 3D cube
    void renderCube();

    // Set up basic camera transformations
    void setCamera();
};

#endif
