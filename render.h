#ifndef RENDER_CLASS_H
#define RENDER_CLASS_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>

struct PaddleState {
	float x_pos = 0.0f;
	float y_pos = -2.3f;
	float z_pos = -10.0f;
	float direction = 0.0f;
};

void key(GLFWwindow* window, int k, int s, int action, int mods);
void updatePaddlePosition(PaddleState* paddleState, double deltaTime);

#endif
