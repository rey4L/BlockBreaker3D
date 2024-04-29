#ifndef BOILERPLATE_CLASS_H
#define BOILERPLATE_CLASS_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/constants.hpp>
#include <vector>
#include <algorithm>

// Blocks postion within the window
const float x = 1.0f;
const float y = 0.35f;
const float z = -3.0f;

// Window color values
const float r = 0.0;
const float g = 0.0;
const float b = 0.0;

void initializeGLFW();
GLFWwindow* createGLFWWindow(int width, int height, const char* title);
void initializeGLAD();
void setupViewport(int width, int height);

#endif