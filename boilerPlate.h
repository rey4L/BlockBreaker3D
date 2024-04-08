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

struct PaddleState {
	float x_pos = -0.2f;
	float y_pos = -1.5f;
	float z_pos = -5.0f;
	float direction = 0.0f;
};

void initializeGLFW();
GLFWwindow* createGLFWWindow(int width, int height, const char* title);
void initializeGLAD();
void setupViewport(int width, int height);
void key(GLFWwindow* window, int k, int s, int action, int mods);
void updateRotation(float& rotation, double& prevTime, const double currentTime, const float rotationSpeed, const double timeInterval);
void bounce(const double currentTime, double previousTime, float& gravity, float& position, float& velocity, float& damping, float& groundLevel, float& minimumVelocity, int& bounceCount, const int maxBounces);

#endif