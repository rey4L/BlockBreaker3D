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

	Cube(glm::vec3 pos, float scl); //object setter
	void render(Shader& shader, int& modelLoc, VAO& vao, const unsigned int* indices, size_t indicesSize);
	bool collidesWith(glm::vec3 point);
};

#endif