# Icarus Core

Icarus Core is the foundation of the Infinia Game Engine, an open-world RPG game engine designed to simplify the creation of games with massive, immersive worlds. The engine is tailored for developers who aim to create RPG experiences akin to The Witcher 3, focusing on ease of use, powerful world-building tools, and flexibility.

## Features (Work in Progress)

SFML Integration: Utilizing the Simple and Fast Multimedia Library (SFML) for rendering and window management.

Dynamic Game Loop: A modular game loop handling events, rendering, and updates.

Input Handling: Basic input systems for user interaction.

Expandable Architecture: Designed to grow as more features are implemented, such as rendering, physics, and AI.

## Project Goals

The primary objective is to develop a robust, user-friendly RPG engine with features like:

Drag-and-drop visual scripting.

Advanced AI and behavior trees.

Terrain generation and open-world editing tools.

Cross-platform support (initially PC and Android).

## Current Progress

The project is currently in the early stages of development. Here's what has been completed so far:

Window Management: Creation of a dynamic SFML window that updates based on user input.

Basic Game Loop: Implementation of a foundational game loop that handles window events and rendering.

## Future milestones include:

Implementing rendering of shapes, sprites, and text.

Adding time management with delta time for smooth animations.

Expanding input handling for keyboard and mouse.

## Getting Started

To build and run the project, follow these steps:

### Prerequisites

*CLion or another C++ IDE.*

*CMake (minimum version 3.10).*

*SFML 2.6.2 (available here).*

*A compiler supporting C++17.*

## Build Instructions

### Clone the repository:

`git clone https://github.com/YourUsername/IcarusCore.git
cd IcarusCore`

## Configure the project:

Set the SFML_DIR in CMakeLists.txt to the path where SFML is installed.

## Build the project:

Open the project in CLion (or your chosen IDE).

Configure CMake and build the project.

Run the executable to test the current features.

## Repository Structure

IcarusCore/
├── include/         # Header files
├── src/             # Source files
├── CMakeLists.txt   # Build configuration
├── README.md        # Project information
└── LICENSE          # License file

## Contributing

Contributions are welcome! Feel free to fork the repository, make changes, and submit a pull request. Please ensure your code adheres to the project's style and standards.

## How to Contribute
```
Fork the repository.

Create a new branch:

`git checkout -b feature-branch`

Commit your changes:

`git commit -m "Add a new feature"`

Push to your branch:

`git push origin feature-branch`

Submit a pull request.
```
## License

This project is licensed under the GNU General Public License v3.0 (GPL-3.0). See the LICENSE file for details.

## Contact

For questions or suggestions, feel free to reach out:

Email: `sirkianmj@gmail.com`

