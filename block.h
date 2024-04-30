#ifndef BLOCK_H
#define BLOCK_H

#include "boilerPlate.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

class Cube {
public:
	glm::vec3 position;
	float scale;
	bool isDestroyed;
	glm::vec3 color;

	Cube(glm::vec3 pos, float scl, const glm::vec3& col); // Object setter
	void render(Shader& shader, int& modelLoc, VAO& vao, const unsigned int* indices, size_t indicesSize);
	bool collidesWith(glm::vec3 point, float radius);
};

#endif