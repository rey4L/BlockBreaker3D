#ifndef VERTICES_CLASS_H
#define VERTICES_CLASS_H

#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

void generateSphere(float radius, unsigned int longitudeCount, unsigned int latitudeCount, std::vector<float>& vertices, std::vector<unsigned int>& indices);

namespace Vertices {
    extern GLuint square_cube_indices[36];
    extern GLfloat cuboid_vertices[192];
    extern GLfloat paddle_vertices[192];
}

#endif // !1