#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "ShaderUtils.h"  // Include the new Shader utility header
#include "Camera.h"       // Include the Camera class header
#include "GameObject.h"   // Include the GameObject class header
#include <glm/gtc/type_ptr.hpp>

int main() {
    // Initialize SFML window
    sf::Window window(sf::VideoMode(800, 600), "Icarus Engine", sf::Style::Close | sf::Style::Resize);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed!" << std::endl;
        return -1;
    }

    // Set up shaders (ensure the correct file paths are passed)
    GLuint shaderProgram = setupShaders();
    if (shaderProgram == 0) {
        std::cerr << "Shader setup failed!" << std::endl;
        return -1;
    }

    // Set up vertex data (example: triangle)
    GLfloat vertices[] = {
            0.0f,  0.5f, 0.0f,  // Top vertex
            -0.5f, -0.5f, 0.0f,  // Bottom left vertex
            0.5f, -0.5f, 0.0f   // Bottom right vertex
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Create a camera at position (0, 0, 3) (a little behind the origin to view the scene)
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

    // Create a GameObject at position (0, 0, 0), with no rotation, and scale of (1, 1, 1)
    GameObject object(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

    // Setup time for deltaTime calculation
    sf::Clock deltaClock;

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Main rendering loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Time step for smooth movement
        float deltaTime = deltaClock.restart().asSeconds();

        // Handle keyboard input for camera movement
        bool forward = false, backward = false, left = false, right = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) forward = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) backward = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) left = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) right = true;

        // Move the camera based on user input
        camera.moveCamera(deltaTime, forward, backward, left, right);

        // Handle mouse input for camera direction
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        static sf::Vector2i lastMousePos = mousePos;
        float offsetX = mousePos.x - lastMousePos.x;
        float offsetY = lastMousePos.y - mousePos.y;  // Reversed because y-coordinates go down
        lastMousePos = mousePos;

        // Update camera direction based on mouse movement
        camera.updateCameraDirection(offsetX, offsetY);

        // Clear the screen (including depth buffer)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);

        // Set up the view and projection matrices
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix(800.0f, 600.0f);  // Using window dimensions

        // Pass the view and projection matrices to the shader
        GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
        GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Render the GameObject
        object.render(shaderProgram);

        // Display the rendered frame
        window.display();
    }

    return 0;
}
