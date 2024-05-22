#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/constants.hpp>
#include <vector>
#include <algorithm>
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "vertices.h"
#include "audio.h"
#include "interface.h"
#include <random>

extern int multiHitCount; //variable to track the blocks with power up potential
extern float length; // Paddle length
extern float radius; // Paddle radius

extern float ball_speed; // Ball speed

extern std::vector<GLfloat> pill_vertices;
extern std::vector<GLuint> pill_indices;

class Cube {
public:
	glm::vec3 position;
	float scale;
	bool isDestroyed;
	glm::vec3 color;

	Cube(glm::vec3 pos, float scl, const glm::vec3& col); 
	void render(Shader& shader, int& modelLoc, VAO& vao, const unsigned int* indices, size_t indicesSize);
	bool collidesWith(glm::vec3 point, float radius);
};

void applyPowerUp(std::vector<Cube>& cubes, float& paddleWidth, float& length, Audio& audio);
bool areAllBlocksDestroyed(const std::vector<Cube>& cubes);

#endif