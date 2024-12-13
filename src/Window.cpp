#include "Window.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>  // Add this line to resolve the 'value_ptr' issue


void checkOpenGLError() {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
}


std::string loadShaderSource(const char* filepath) {
    std::ifstream shaderFile(filepath);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

GLuint compileShader(GLenum shaderType, const std::string& source) {
    GLuint shader = glCreateShader(shaderType);
    const char* shaderSource = source.c_str();
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        char* errorLog = new char[logLength];
        glGetShaderInfoLog(shader, logLength, &logLength, errorLog);
        std::cerr << "Shader compilation failed: " << errorLog << std::endl;
        delete[] errorLog;
    }
    return shader;
}

GLuint createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
        char* errorLog = new char[logLength];
        glGetProgramInfoLog(shaderProgram, logLength, &logLength, errorLog);
        std::cerr << "Shader program linking failed: " << errorLog << std::endl;
        delete[] errorLog;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
Window::Window() : window(sf::VideoMode(800, 600), "Icarus Engine") {
    initOpenGL();
    loadShaders();
    setupBuffers();
}

void Window::initOpenGL() {
    glewInit();
    glEnable(GL_DEPTH_TEST);
}

void Window::loadShaders() {
    std::string vertexSource = loadShaderSource("vertex_shader.glsl");
    std::string fragmentSource = loadShaderSource("fragment_shader.glsl");

    shaderProgram = createShaderProgram(vertexSource, fragmentSource);

    if (shaderProgram == 0) {
        std::cerr << "Shader program creation failed!" << std::endl;
        // Handle the error appropriately. For example, exit the application or prevent further rendering.
        exit(EXIT_FAILURE); // or return if you want to recover gracefully
    }
}
void Window::setupBuffers() {
    GLfloat vertices[] = {
            // Positions         // Colors
            -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Bottom-left, Red
            0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom-right, Green
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // Top, Blue
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Window::renderCube() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);

    // Set transformation matrices
    model = glm::mat4(1.0f);
    view = glm::lookAt(glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Draw
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3); // Drawing a triangle
    glBindVertexArray(0);

    checkOpenGLError();
    std::cout << "Using shader program: " << shaderProgram << std::endl;
}


void Window::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Window::runGameLoop() {
    while (window.isOpen()) {
        handleEvents();
        renderCube();
        window.display();
    }
}
