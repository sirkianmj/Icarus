#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Window {
private:
    sf::RenderWindow window;
    std::string windowTitle;
    int width, height;

public:
    // Constructor to initialize the window with a title and size
    Window();

    // Display current window properties
    void displayProperties();

    // Handle user input for new title, width, and height
    void handleUserInput();

    // Main game loop to run the window and handle events
    void runGameLoop();
};

#endif
