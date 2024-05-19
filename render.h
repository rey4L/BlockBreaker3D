#ifndef RENDER_CLASS_H
#define RENDER_CLASS_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <random>
#include "particleSystem.h"
#include "audio.h"
#include "interface.h"

// Ball velocity variables
extern float ball_velocity_x;
extern float ball_velocity_y;

struct PaddleState {
	float x_pos = 0.0f;
	float y_pos = -2.3f;
	float z_pos = -10.0f;
	float direction = 0.0f;
};

void key(GLFWwindow* window, int k, int s, int action, int mods);
void updatePaddlePosition(PaddleState* paddleState, double deltaTime, ParticleSystem& particleSystem);
void updateBallPosition(float& tra_x, float& position_y, float& tra_z,
	float& ball_velocity_x, float& ball_velocity_y, float& ball_velocity_z,
	float deltaTime, Audio& audio, bool& isGameOver);
void handlePaddleCollision(glm::vec3& spherePosition, glm::vec3& velocity, glm::vec3& paddlePos,
	float sphereRadius, float& ball_velocity_x, float& ball_velocity_y,
	float& ball_velocity_z, Audio& audio, float paddleWidth, float paddleHeight,
	float paddleDepth);
void randomizeTrajectory(float speed);
void incrementScore(int points);

#endif