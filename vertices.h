#ifndef VERTICES_CLASS_H
#define VERTICES_CLASS_H

#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/constants.hpp>

const int segments = 64; // Control the LOD or smoothness of the generated cylinder

void generateSphere(float radius, unsigned int longitudeCount, unsigned int latitudeCount, std::vector<float>& vertices, std::vector<unsigned int>& indices);
void generateCylinderVertices(std::vector<GLfloat>& vertices, float radius, float length);
void generateSphereVertices(std::vector<GLfloat>& vertices, float radius, float length);
void generateCylinderIndices(std::vector<GLuint>& indices);
void generateSphereIndices(std::vector<GLuint>& indices);
void generatePillVertices(std::vector<GLfloat>& vertices, float radius, float length);
void generatePillIndices(std::vector<GLuint>& indices);
void updatePaddleVertices(std::vector<GLfloat>& pill_vertices, std::vector<GLuint>& pill_indices, float radius, float length);

namespace Vertices {
    extern GLuint square_cube_indices[36];
    extern GLfloat cuboid_vertices[192];
}

#endif