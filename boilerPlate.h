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

void initializeGLFW();
GLFWwindow* createGLFWWindow(int width, int height, const char* title);
void initializeGLAD();
void setupViewport(int width, int height);

#endif