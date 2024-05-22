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
#include "VBO.h"
#include "block.h"
#include "interface.h"
#include "audio.h"
#include "vertices.h"
#include "render.h"

// Blocks postion within the window
const float x = -0.2f;
const float y = -0.15f;
const float z = -0.5f;

// Window color values
const float r = 0.15;
const float g = 0.15;
const float b = 0.15;

// Translation matrix values for the ball
extern float tra_x;
extern float tra_y;
extern float tra_z; // z-value of the scene and paddle + z-value of the blocks;

// Rotation matrix values for the ball
extern const float rot_x;
extern const float rot_y;
extern const float rot_z;

// Define the game world boundaries
extern const float gameWorldMinX;
extern const float gameWorldMaxX;
extern const float gameWorldMinY;
extern const float gameWorldMaxY;
extern const float gameWorldZ;

// Calculate the block spacing and size
extern const float blockSpacingX;
extern const float blockSpacingY;
extern const float blockSize;

// Ball velocity
extern float ball_velocity_x;
extern float ball_velocity_y;
extern float ball_velocity_z;

extern float position_y;

// Ball speed
extern float ball_speed;

// Paddle related constants
extern float paddleWidth; // percentage of the pill the ball sees
extern float paddleHeight;
extern float paddleDepth;

// Set paddle radius and legth
extern float radius;
extern float length;

extern glm::vec3 cubeColors[12];
extern int currentColorIndex;
extern std::vector<Cube> cubes;

void initializeGLFW();
GLFWwindow* createGLFWWindow(int width, int height, const char* title);
void initializeGLAD();
void setupViewport(int width, int height);
void colorBufferInit(float r, float g, float b);
void resetGameState(Audio& audio);

#endif