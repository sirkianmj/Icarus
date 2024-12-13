#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Function declaration for setting up shaders
GLuint setupShaders();
void checkCompileErrors(GLuint shader, const std::string& type);
GLuint compileShader(GLenum type, const char* source); // Declare compileShader function
GLuint setupShaders();

#endif
