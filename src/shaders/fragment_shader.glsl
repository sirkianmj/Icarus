#version 330 core

in vec3 ourColor;  // Input color from the vertex shader
out vec4 FragColor; // Final color output

void main() {
    FragColor = vec4(ourColor, 1.0); // Use the passed color
}
