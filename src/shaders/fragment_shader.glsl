#version 330 core

in vec3 vertexColor; // Input from vertex shader

out vec4 FragColor; // Output color to the framebuffer

void main() {
    // Set the fragment color to the vertex color
    FragColor = vec4(vertexColor, 1.0f);
}
