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
#include <random>
#include "block.h"
#include "interface.h"
#include "audio.h"

// Blocks postion within the window
const float x = 1.0f;
const float y = 0.25f;
const float z = -2.5f;

// Window color values
const float r = 0.01;
const float g = 0.01;
const float b = 0.01;

// Addition

// Translation matrix values for the ball
extern float tra_x;
extern float tra_y;
extern float tra_z; // z-value of the scene and paddle + z-value of the blocks;

// Rotation matrix values for the ball
extern const float rot_x;
extern const float rot_y;
extern const float rot_z;

// Ball velocity
extern float ball_velocity_x;
extern float ball_velocity_y;
extern float ball_velocity_z;

extern float position_y;

extern glm::vec3 cubeColors[12];
extern int currentColorIndex;
extern std::vector<Cube> cubes;

void initializeGLFW();
GLFWwindow* createGLFWWindow(int width, int height, const char* title);
void initializeGLAD();
void setupViewport(int width, int height);
void resetGameState(Audio& audio);
void applyPowerUp(std::vector<Cube>& cubes);

#endif