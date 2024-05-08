#ifndef RENDER_CLASS_H
#define RENDER_CLASS_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>

struct PaddleState {
	float x_pos = 1.0f;
	float y_pos = -2.3f;
	float z_pos = -10.0f;
	float direction = 0.0f;
};

void key(GLFWwindow* window, int k, int s, int action, int mods);
void updateRotation(float& rotation, double& prevTime, const double currentTime, const float rotationSpeed, const double timeInterval);
void bounce(const double currentTime, double previousTime, float& gravity, float& position, float& velocity, float& damping, float& groundLevel, float& minimumVelocity, int& bounceCount, const int maxBounces);
void updatePaddlePosition(PaddleState* paddleState, double deltaTime);

#endif
