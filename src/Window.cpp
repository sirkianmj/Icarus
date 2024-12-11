#include "Window.h"
#include <iostream>
#include <limits> // Add this line

Window::Window() : windowTitle("Initial Title"), width(800), height(600) {
    window.create(sf::VideoMode(width, height), windowTitle); // Create the SFML window
}

void Window::displayProperties() {
    std::cout << "Window Title: " << windowTitle << std::endl;
    std::cout << "Width: " << width << ", Height: " << height << std::endl;
}

void Window::handleUserInput() {
    // Ask for window title
    std::cout << "Enter window title: ";
    std::getline(std::cin, windowTitle);

    // Ask for new width
    std::cout << "Enter new width: ";
    std::cin >> width;

    // Clear the input buffer to ignore any leftover characters
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    // Ask for new height
    std::cout << "Enter new height: ";
    std::cin >> height;

    // Clear the input buffer again after height input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    // Update window size
    window.setSize(sf::Vector2u(width, height));
    window.setTitle(windowTitle);  // Update window title as well

    // Display updated properties
    displayProperties();
}

void Window::runGameLoop() {
    bool running = true;
    while (running) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  // Close window on close event
                running = false; // Exit the game loop
            }
        }

        // Clear window (black background)
        window.clear(sf::Color::Black);

        // Display the window content
        window.display();

        // Handle user input (continuously ask for title, width, and height)
        handleUserInput();
    }
}
