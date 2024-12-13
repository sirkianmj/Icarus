#version 330 core

layout(location = 0) in vec3 aPos;  // Vertex position
layout(location = 1) in vec3 aColor; // Vertex color

out vec3 ourColor;  // Pass color to fragment shader

uniform mat4 model;      // Model matrix (transforms object)
uniform mat4 view;       // View matrix (camera)
uniform mat4 projection; // Projection matrix (perspective or orthogonal)

void main()
{
    ourColor = aColor;  // Pass color to fragment shader
    gl_Position = projection * view * model * vec4(aPos, 1.0); // Apply transformations to vertex position
}
